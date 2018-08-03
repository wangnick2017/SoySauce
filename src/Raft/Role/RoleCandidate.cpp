//
// Created by wangnick on 7/26/18.
//

#include "RoleCandidate.h"
#include "Timer.h"

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct RoleCandidate::Impl
        {
            Timer timer;
        };

        RoleCandidate::RoleCandidate(State &s, ServerInfo &i, Transformer &t)
            : RoleBase(s, i, t), pImpl(make_unique<Impl>())
        {
        }

        RoleCandidate::~RoleCandidate() = default;

        void RoleCandidate::Init()
        {
            ++state.currentTerm;
            //state.votedFor = ;
            pImpl->timer.Reset(Random(info.timeout, info.timeout * 2));
            pImpl->timer.Start();
        }

        void RoleCandidate::Leave()
        {
            pImpl->timer.Stop();
        }

        RPCReply RoleCandidate::RPCAppendEntries(const AppendEntriesRPC &message)
        {
        }

        RPCReply RoleCandidate::RPCRequestVote(const RequestVoteRPC &message)
        {
        }

        bool RoleCandidate::Put(const string &key, const string &value)
        {
            return false;
        }

        pair<bool, string> RoleCandidate::Get(const string &key)
        {
            return make_pair(false, "");
        }
    }
}