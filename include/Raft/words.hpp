//
// Created by wangnick on 7/26/18.
//

#pragma once

#include "ServerInfo.h"

namespace Soy
{
    namespace Raft
    {
        using Term = std::uint64_t;
        using Index = std::uint64_t;

        struct Entry
        {
            std::string op, arg;
            Term term;
        };

        struct AppendEntriesRPC
        {
            Term term, prevLogTerm;
            ServerID leaderID;
            Index prevLogIndex, leaderCommit;
            AppendEntriesRPC(Term t, Term pt, Index pi, Index lc, ServerID l)
                : term(t), prevLogTerm(pt), prevLogIndex(pi), leaderCommit(lc), leaderID(l)
            {
            }
        };

        struct RequestVoteRPC
        {
            Term term, lastLogTerm;
            Index lastLogIndex;
            ServerID candidateID;
            RequestVoteRPC(Term t, Term lt, Index li, ServerID c)
                : term(t), lastLogTerm(lt), lastLogIndex(li), candidateID(c)
            {
            }
        };

        struct RPCReply
        {
            Term term;
            bool ans;
        };
    }
}
