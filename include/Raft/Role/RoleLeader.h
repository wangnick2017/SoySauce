//
// Created by wangnick on 7/25/18.
//

#pragma once

#include "RoleBase.h"

namespace Soy
{
    namespace Raft
    {
        class RoleLeader : public RoleBase
        {
        public:
            RoleLeader(State &s, ServerInfo &i, Transformer &t, Rpc::RaftRpcClient &c);
            ~RoleLeader() override;
            void Init() override;
            void ReInit(Term t, const std::string &s) override;
            void Leave() override;
            RPCReply RPCAppendEntries(const AppendEntriesRPC &message) override;
            RPCReply RPCRequestVote(const RequestVoteRPC &message) override;
            bool Put(const std::string &key, const std::string &value) override;
            std::pair<bool, std::string> Get(const std::string &key) override;

            void SendHeartbeat() override;
            std::pair<RPCReply, bool> SendAppendEntries(
                int sth, const Rpc::AppendEntriesMessage &m, uint64_t timeout = 0);

        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
        };
    }
}
