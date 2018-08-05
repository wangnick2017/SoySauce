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
            if (message.prevLogIndex > state.log.size() || state.log[message.prevLogIndex].term != message.prevLogTerm)
            {
                return RPCReply(state.currentTerm, false);
            }
            //
            //
            //
            if (state.commitIndex > state.lastApplied)
            {
                state.machine[state.log[state.lastApplied].op] = state.log[state.lastApplied].arg;
                ++state.lastApplied;
            }
            pImpl->timer.Restart();
        }

        RPCReply RoleFollower::RPCRequestVote(const RequestVoteRPC &message)
        {
            if (message.term < state.currentTerm)
            {
                return RPCReply(state.currentTerm, false);
            }
            string v = state.votedFor.ToString();
            if ((v.empty() || v == message.candidateID.ToString()) &&
                (message.lastLogTerm > state.currentTerm ||
                 message.lastLogTerm == state.currentTerm && message.lastLogIndex >= state.commitIndex))
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