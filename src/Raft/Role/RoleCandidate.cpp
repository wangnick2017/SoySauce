//
// Created by wangnick on 7/26/18.
//

#include "RoleCandidate.h"
#include "Timer.h"
#include "RaftRpcClient.hpp"
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include "random.h"

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
            pImpl->timer.Reset(Random(info.electionTimeout, info.electionTimeout * 2));
            pImpl->timer.Start();
            Rpc::RequestVoteMessage message;
            message.set_term(state.currentTerm);
            message.set_lastlogindex(state.log.size() - 1);
            if (state.log.size() > 0)
                message.set_lastlogterm(state.log[state.log.size() - 1].term);
            message.set_candidateid(info.local.ToString());
            int size = (int)client.Stubs.size();
            vector<boost::unique_future<pair<RPCReply, bool>>> f;
            for (int i = 0; i < size; ++i)
            {
                f.push_back(boost::async(move(boost::bind(
                    &Rpc::RaftRpcClient::SendRequestVote, &client, i, message))));
            }
            for (int i = 0; i < size; ++i)
            {
                const auto &result = f[i].get();
                if (result.second)
                {
                    if (result.first.ans)
                        ++pImpl->sum;
                    else if (result.first.term > message.term())
                        transformer.TransformSafe(RoleTh::Follower, result.first.term);
                }
            }
            if (pImpl->sum * 2 > size)
                transformer.TransformSafe(RoleTh::Leader, state.currentTerm);
        }

        void RoleCandidate::Leave()
        {
            pImpl->timer.Stop();
        }

        RPCReply RoleCandidate::RPCAppendEntries(const AppendEntriesRPC &message)
        {
            if (message.term > state.currentTerm)
                transformer.TransformSafe(RoleTh::Follower, message.term);
            return RPCReply(state.currentTerm, false);
        }

        RPCReply RoleCandidate::RPCRequestVote(const RequestVoteRPC &message)
        {
            if (message.term > state.currentTerm)
                transformer.TransformSafe(RoleTh::Follower, message.term);
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