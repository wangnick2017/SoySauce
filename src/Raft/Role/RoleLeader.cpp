//
// Created by wangnick on 7/26/18.
//

#include "words.hpp"
#include "RoleLeader.h"
#include "Timer.h"
#include "RaftRpcClient.hpp"
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include "random.h"

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
                //BOOST_LOG_TRIVIAL(info) << "heartbeat is sending now";
                //SendHeartbeat();
                transformer.Sender();
            });
        }

        RoleLeader::~RoleLeader() = default;

        void RoleLeader::Init()
        {
            BOOST_LOG_TRIVIAL(info) << "leader init " + to_string(state.currentTerm);
            int size = state.nextIndex.size();
            for (int i = 0; i < size; ++i)
            {
                state.nextIndex[i] = state.log.size();
                state.matchIndex[i] = -1;
            }
            pImpl->timer.Reset(Random(info.heartbeatTimeout, info.heartbeatTimeout * 2), true);
            SendHeartbeat();
            pImpl->timer.Start();
        }

        void RoleLeader::Leave()
        {
            pImpl->timer.Stop();
            BOOST_LOG_TRIVIAL(info) << "leader leave";
        }

        RPCReply RoleLeader::RPCAppendEntries(const AppendEntriesRPC &message)
        {
            //BOOST_LOG_TRIVIAL(info) << "leader deal append";
            if (message.term > state.currentTerm)
                transformer.TransformSafe(RoleTh::Follower, message.term);
            return RPCReply(state.currentTerm, false);
        }

        RPCReply RoleLeader::RPCRequestVote(const RequestVoteRPC &message)
        {
            //BOOST_LOG_TRIVIAL(info) << "leader deal request";
            if (message.term > state.currentTerm)
                transformer.TransformSafe(RoleTh::Follower, message.term);
            return RPCReply(state.currentTerm, false);
        }

        bool RoleLeader::Put(const string &key, const string &value)
        {
            BOOST_LOG_TRIVIAL(info) << "leader deal put";
            state.log.push_back((Entry){key, value, state.currentTerm});
            int size = (int)client.Stubs.size();
            boost::future<pair<RPCReply, bool>> f[10];
            for (int i = 0; i < size; ++i)
            {
                if (i == client.LocalNumber)
                    continue;
                BOOST_LOG_TRIVIAL(info) << "put senting - " + to_string(i);
                Rpc::AppendEntriesMessage message;
                message.set_term(state.currentTerm);
                message.set_leaderid(info.localRaft.ToString());
                message.set_prevlogindex(state.nextIndex[i] - 1);
                if (state.nextIndex[i] > 0)
                    message.set_prevlogterm(state.log[state.nextIndex[i] - 1].term);
                message.set_leadercommit(state.commitIndex);
                for (int j = (int)state.log.size() - 1; j >= state.nextIndex[i] && j >= 0; --j)
                {
                    Rpc::Entry e;
                    e.set_term(state.currentTerm);
                    e.set_key(state.log[j].op);
                    e.set_args(state.log[j].arg);
                    *message.add_entries() = move(e);
                }
                f[i] = (boost::async(move(boost::bind(
                    &RoleLeader::SendAppendEntries, this, i, message, broadcastTimeout * 3))));
            }
            //BOOST_LOG_TRIVIAL(info) << "put sent";
            int may = 0xfffff, cnt = 1;
            for (int i = 0; i < size; ++i)
            {
                if (i == client.LocalNumber)
                    continue;
                const auto result = f[i].get();
                //BOOST_LOG_TRIVIAL(info) << "put sent and get++";
                if (result.second)
                {
                    may = min(may, (int)state.matchIndex[i]);
                    ++cnt;
                }
                else if (result.first.ans)
                {
                    transformer.TransformSafe(RoleTh::Follower, result.first.term);
                    return false;
                }
            }
            if (may > state.commitIndex && cnt + cnt > size)
                state.commitIndex = may;
            while (state.commitIndex > state.lastApplied)
            {
                ++state.lastApplied;
                state.machine[state.log[state.lastApplied].op] = state.log[state.lastApplied].arg;
            }
            return state.commitIndex == state.log.size() - 1;
        }
        template <class Tp>
        decltype(auto) timeFrom(const Tp &tp)
        {
            return boost::chrono::duration_cast<boost::chrono::milliseconds>
                (boost::chrono::system_clock::now() - tp).count();
        }
        pair<RPCReply, bool> RoleLeader::SendAppendEntries(int sth, const Rpc::AppendEntriesMessage &m, uint64_t timeout)
        {
            Rpc::AppendEntriesMessage message{m};
            auto startTime = boost::chrono::system_clock::now();
            do
            {
                grpc::ClientContext ctx;
                ctx.set_deadline(std::chrono::system_clock::now()+std::chrono::milliseconds(broadcastTimeout));
                Rpc::Reply reply;
                auto status = client.Stubs[sth]->AppendEntries(&ctx, message, &reply);
                if (status.ok())
                {
                    if (!reply.ans())
                    {
                        if (message.term() < reply.term())
                        {
                            return make_pair(RPCReply(reply.term(), true), false);
                        }
                        else
                        {
                            if (state.nextIndex[sth] == 0)
                            {
                                continue;
                            }
                            --state.nextIndex[sth];
                            message.set_prevlogindex(state.nextIndex[sth] - 1);
                            if (state.nextIndex[sth] > 0)
                                message.set_prevlogterm(state.log[state.nextIndex[sth] - 1].term);
                            Rpc::Entry e;
                            e.set_term(state.currentTerm);
                            e.set_key(state.log.at(state.nextIndex.at(sth)).op);
                            e.set_args(state.log.at(state.nextIndex.at(sth)).arg);
                            *message.add_entries() = move(e);
                        }
                    }
                    else
                    {
                        state.matchIndex[sth] = state.log.size() - 1;
                        state.nextIndex[sth] = state.matchIndex[sth] + 1;
                        return make_pair(RPCReply(reply.term(), true), true);
                    }
                }
            }
            while (timeFrom(startTime) <= timeout);
            return make_pair(RPCReply(0, false), false);
        }

        pair<bool, string> RoleLeader::Get(const string &key)
        {
            BOOST_LOG_TRIVIAL(info) << "leader deal get";
            if (state.machine.find(key) == state.machine.end())
                return make_pair(false, "");
            return make_pair(true, state.machine[key]);
        }

        void RoleLeader::SendHeartbeat()
        {
            Rpc::AppendEntriesMessage message;
            message.set_term(state.currentTerm);
            message.set_leaderid(info.localRaft.ToString());
            message.set_leadercommit(state.commitIndex);
            message.clear_entries();
            int size = (int)client.Stubs.size();
            boost::future<pair<RPCReply, bool>> f[10];
            for (int i = 0; i < size; ++i)
            {
                if (i == client.LocalNumber)
                    continue;
                message.set_prevlogindex(state.nextIndex[i] - 1);
                if (state.nextIndex[i] > 0)
                    message.set_prevlogterm(state.log[state.nextIndex[i] - 1].term);
                f[i] = boost::async(move(boost::bind(
                    &Rpc::RaftRpcClient::SendAppendEntries, &client, i, message, false, 0)));
            }
            for (int i = 0; i < size; ++i)
            {
                if (i == client.LocalNumber)
                    continue;
                const auto &result = f[i].get();
                //BOOST_LOG_TRIVIAL(info) << "put sent and get++";
                if (result.first.term > state.currentTerm)
                {
                    transformer.TransformSafe(RoleTh::Follower, result.first.term);
                }
            }
        }
    }
}
