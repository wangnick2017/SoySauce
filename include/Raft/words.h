//
// Created by wangnick on 7/26/18.
//

#pragma once

#include "../ServerInfo.h"

namespace Soy
{
    namespace Raft
    {
        using Term = std::uint64_t;
        using Index = std::uint64_t;

        struct Entry
        {
            string op, arg;
            Term term;
        };

        struct AppendEntriesRPC
        {
            Term term, prevLogTerm;
            ServerID leaderID;
            Index prevLogIndex, leaderCommit;
        };

        struct RequestVoteRPC
        {
            Term term, lastLogTerm;
            Index lastLogIndex;
            ServerID candidateID;
        };
    }
}
