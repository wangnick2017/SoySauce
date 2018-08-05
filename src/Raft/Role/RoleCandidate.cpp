//
// Created by wangnick on 7/26/18.
//

#include "RoleCandidate.h"
#include "Timer.h"
#include "RaftRpcClient.hpp"

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct RoleCandidate::Impl
        {
            Timer timer;
            int sum;
        };

        RoleCandidate::RoleCandidate(State &s, ServerInfo &i, Transformer &t, Rpc::RaftRpcClient &c)
            : RoleBase(s, i, t, c), pImpl(make_unique<Impl>())
        {
            pImpl->timer.Bind([this]
            {
                transformer.Transform(RoleTh::Follower, state.currentTerm + 1);
            });
        }

        RoleCandidate::~RoleCandidate() = default;

        void RoleCandidate::Init()
        {
            state.votedFor = info.local;
            pImpl->sum = 1;
            pImpl->timer.Reset(Random(info.timeout, info.timeout * 2));
            pImpl->timer.Start();
            Rpc::RequestVoteMessage message;
            message.set_term(state.currentTerm);
            message.set_lastlogterm(state.log[state.commitIndex].term);
            message.set_lastlogindex(state.commitIndex);
            message.set_candidateid(info.local.ToString());
            for (auto &stub : client.Stubs)
            {
                grpc::ClientContext ctx;
                //ctx...
                Rpc::Reply reply;
                auto status = stub->RequestVote(&ctx, message, &reply);
                if (status.ok())
                {
                    if (reply.ans())
                        ++pImpl->sum;
                    else if (reply.term() > state.currentTerm)
                        transformer.Transform(RoleTh::Follower, reply.term());
                }
            }
            if (pImpl->sum * 2 > client.Stubs.size())
                transformer.Transform(RoleTh::Leader, state.currentTerm);
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
            if (message.term > state.currentTerm)
                transformer.Transform(RoleTh::Follower, message.term);
            return RPCReply(state.currentTerm, false);
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