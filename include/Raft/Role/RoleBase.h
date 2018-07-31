//
// Created by wangnick on 7/25/18.
//

#pragma once

#include "Base.h"
#include "words.h"

namespace Soy
{
    namespace Raft
    {
        const int RoleNumber = 3;

        enum class RoleTh
        {
            Follower, Candidate, Leader, Dead
        };

        class RoleBase
        {
        public:
            virtual ~RoleBase() = default;
            virtual void Init() = 0;
            virtual void Leave() = 0;
            virtual Reply RPCAppendEntries(AppendEntriesRPC message) = 0;
            virtual Reply RPCRequestVote(RequestVoteRPC message) = 0;

        protected:
            Term currentTerm;
            ServerID votedFor;
            std::vector<Entry> log;

            Index commitIndex, lastApplied;

            std::map<std::string, std::string> stateMachine;
        };
    }
}