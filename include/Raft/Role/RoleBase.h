//
// Created by wangnick on 7/25/18.
//

#pragma once

#include "Base.h"
#include "words.hpp"
#include "Transformer.hpp"
#include "RaftRpcClient.hpp"

namespace Soy
{
    namespace Raft
    {
        const int RoleNumber = 3;

        class RoleBase
        {
        public:
            RoleBase(State &s, ServerInfo &i, Transformer &t, Rpc::RaftRpcClient &c);
            virtual ~RoleBase() = default;
            virtual void Init() = 0;
            virtual void ReInit(Term t, const std::string &s) = 0;
            virtual void Leave() = 0;
            virtual RPCReply RPCAppendEntries(const AppendEntriesRPC &message) = 0;
            virtual RPCReply RPCRequestVote(const RequestVoteRPC &message) = 0;
            virtual bool Put(const std::string &key, const std::string &value) = 0;
            virtual std::pair<bool, std::string> Get(const std::string &key) = 0;
            virtual void SendHeartbeat();

        protected:
            State &state;
            ServerInfo &info;
            Transformer &transformer;
            Rpc::RaftRpcClient &client;
        };
    }
}