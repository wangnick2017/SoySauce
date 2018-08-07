//
// Created by wangnick on 7/26/18.
//

#pragma once

#include "Base.h"
#include "ServerInfo.h"

namespace Soy
{
    namespace Raft
    {
        const std::uint64_t broadcastTimeout = 20;

        enum class RoleTh
        {
            Follower, Candidate, Leader, Dead
        };

        using Term = std::uint64_t;
        using Index = std::int64_t;

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
            std::vector<Entry> entries;
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
            RPCReply(Term t = 0, bool a = false)
                : term(t), ans(a)
            {
            }
        };

        struct State
        {
            Term currentTerm;
            ServerID votedFor;
            std::vector<Entry> log;

            Index commitIndex, lastApplied;

            std::map<std::string, std::string> machine;

            std::vector<Index> nextIndex, matchIndex;
        };
    }
}
