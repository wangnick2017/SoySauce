//
// Created by wangnick on 7/26/18.
//

#include "RoleLeader.h"
#include "Timer.h"

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct RoleLeader::Impl
        {
            Timer timer;
        };

        RoleLeader::RoleLeader(State &s, ServerInfo &i, Transformer &t, Rpc::RaftRpcClient &c)
            : RoleBase(s, i, t, c), pImpl(make_unique<Impl>())
        {
            pImpl->timer.Bind([this]
            {
                //transformer.Transform(RoleTh::Follower, state.currentTerm + 1);
            });
        }

        RoleLeader::~RoleLeader() = default;

        void RoleLeader::Init()
        {
            pImpl->timer.Reset(Random(info.timeout, info.timeout * 2));
            pImpl->timer.Start();
        }

        void RoleLeader::Leave()
        {
            pImpl->timer.Stop();
        }

        RPCReply RoleLeader::RPCAppendEntries(const AppendEntriesRPC &message)
        {
        }

        RPCReply RoleLeader::RPCRequestVote(const RequestVoteRPC &message)
        {
            if (message.term > state.currentTerm)
                transformer.Transform(RoleTh::Follower, message.term);
            return RPCReply(state.currentTerm, false);
        }

        bool RoleLeader::Put(const string &key, const string &value)
        {
        }

        pair<bool, string> RoleLeader::Get(const string &key)
        {
        }
    }
}
