//
// Created by wangnick on 7/26/18.
//

#include "RoleFollower.h"
#include "Timer.h"

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct RoleFollower::Impl
        {
            Timer timer;
        };

        RoleFollower::RoleFollower(State &s, ServerInfo &i, Transformer &t, Rpc::RaftRpcClient &c)
            : RoleBase(s, i, t, c), pImpl(make_unique<Impl>())
        {
            pImpl->timer.Bind([this]
            {
                transformer.Transform(RoleTh::Candidate, state.currentTerm + 1);
            });
        }

        RoleFollower::~RoleFollower() = default;

        void RoleFollower::Init()
        {
            state.votedFor = ServerID();
            pImpl->timer.Reset(Random(info.timeout, info.timeout * 2));
            pImpl->timer.Start();
        }

        void RoleFollower::Leave()
        {
            pImpl->timer.Stop();
        }

        RPCReply RoleFollower::RPCAppendEntries(const AppendEntriesRPC &message)
        {
            if (message.term < state.currentTerm)
            {
                return RPCReply(state.currentTerm, false);
            }
            if (message.term > state.currentTerm)
                state.currentTerm = message.term;
            if (message.prevLogIndex >= state.log.size() || state.log[message.prevLogIndex].term != message.prevLogTerm)
            {
                pImpl->timer.Restart();
                return RPCReply(state.currentTerm, false);
            }
            while (state.log.size() - 1 > message.prevLogIndex)
                state.log.pop_back();
            for (const auto &entry : message.entries)
                state.log.push_back(entry);
            if (message.leaderCommit > state.commitIndex)
                state.commitIndex = min(message.leaderCommit, state.log.size() - 1);
            while (state.commitIndex > state.lastApplied)
            {
                state.machine[state.log[state.lastApplied].op] = state.log[state.lastApplied].arg;
                ++state.lastApplied;
            }
            pImpl->timer.Restart();
            return RPCReply(state.currentTerm, true);
        }

        RPCReply RoleFollower::RPCRequestVote(const RequestVoteRPC &message)
        {
            if (message.term < state.currentTerm)
            {
                return RPCReply(state.currentTerm, false);
            }
            if (message.term > state.currentTerm)
                state.currentTerm = message.term;
            string v = state.votedFor.ToString();
            if ((v.empty() || v == message.candidateID.ToString()) &&
                (message.lastLogTerm > state.log.[state.log.size() - 1].term ||
                 message.lastLogTerm == state.log.[state.log.size() - 1].term &&
                 message.lastLogIndex >= state.log.size() - 1))
            {
                state.votedFor = message.candidateID;
                pImpl->timer.Restart();
                return RPCReply(state.currentTerm, true);
            }
            pImpl->timer.Restart();
            return RPCReply(state.currentTerm, false);
        }

        bool RoleFollower::Put(const string &key, const string &value)
        {
            return false;
        }

        pair<bool, string> RoleFollower::Get(const string &key)
        {
            return make_pair(false, "");
        }
    }
}