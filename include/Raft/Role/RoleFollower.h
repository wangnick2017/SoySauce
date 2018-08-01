//
// Created by wangnick on 7/25/18.
//

#pragma once

#include "RoleBase.h"

namespace Soy
{
    namespace Raft
    {
        class RoleFollower : public RoleBase
        {
        public:
            RoleFollower();
            ~RoleFollower() override;
            void Init() override;
            void Leave() override;
            RPCReply RPCAppendEntries(const AppendEntriesRPC &message) override;
            RPCReply RPCRequestVote(const RequestVoteRPC &message) override;
            void Put(const std::string &key, const std::string &value) override;
            std::string Get(const std::string &key) override;

        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
        };
    }
}

