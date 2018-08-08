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
                //BOOST_LOG_TRIVIAL(info) << "candidate to next";
                transformer.Transform(RoleTh::Candidate, state.currentTerm + 1);
            });
        }

        RoleCandidate::~RoleCandidate() = default;

        void RoleCandidate::Init()
        {
            BOOST_LOG_TRIVIAL(info) << "candidate init " + to_string(state.currentTerm);
            state.votedFor = info.localRaft;
            pImpl->sum = 1;
            pImpl->timer.Reset(Random(info.electionTimeout, info.electionTimeout * 2));
            pImpl->timer.Start();
            Rpc::RequestVoteMessage message;
            message.set_term(state.currentTerm);
            message.set_lastlogindex(state.log.size() - 1);
            if (state.log.size() > 0)
                message.set_lastlogterm(state.log[state.log.size() - 1].term);
            message.set_candidateid(info.localRaft.ToString());
            int size = (int)client.Stubs.size();
            boost::future<pair<RPCReply, bool>> f[10];
            for (int i = 0; i < size; ++i)
            {
                if (i == client.LocalNumber)
                    continue;
                f[i] = (boost::async(move(boost::bind(
                    &Rpc::RaftRpcClient::SendRequestVote, &client, i, message))));
            }
            //BOOST_LOG_TRIVIAL(info) << "sent";
            for (int i = 0; i < size; ++i)
            {
                if (i == client.LocalNumber)
                    continue;
                //BOOST_LOG_TRIVIAL(info) << "before get";
                const auto &result = f[i].get();
                //BOOST_LOG_TRIVIAL(info) << "get++" + to_string(result.second);
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
            //BOOST_LOG_TRIVIAL(info) << "init end";
        }

        void RoleCandidate::Leave()
        {
            pImpl->timer.Stop();
            BOOST_LOG_TRIVIAL(info) << "candidate leave";
        }

        RPCReply RoleCandidate::RPCAppendEntries(const AppendEntriesRPC &message)
        {
            //BOOST_LOG_TRIVIAL(info) << "candidate deal append";
            if (message.term > state.currentTerm)
                transformer.TransformSafe(RoleTh::Follower, message.term);
            return RPCReply(state.currentTerm, false);
        }

        RPCReply RoleCandidate::RPCRequestVote(const RequestVoteRPC &message)
        {
            //BOOST_LOG_TRIVIAL(info) << "candidate deal request";
            if (message.term > state.currentTerm)
                transformer.TransformSafe(RoleTh::Follower, message.term);
            return RPCReply(state.currentTerm, false);
        }

        bool RoleCandidate::Put(const string &key, const string &value)
        {
            //BOOST_LOG_TRIVIAL(info) << "candidate deal put";
            return false;
        }

        pair<bool, string> RoleCandidate::Get(const string &key)
        {
            //BOOST_LOG_TRIVIAL(info) << "candidate deal get";
            return make_pair(false, "");
        }
    }
}