//
// Created by wangnick on 7/26/18.
//

#include "RoleLeader.h"
#include "Timer.h"
#include "RaftRpcClient.hpp"
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

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
                SendHeartbeat();
            });
        }

        RoleLeader::~RoleLeader() = default;

        void RoleLeader::Init()
        {
            pImpl->timer.Reset(Random(info.timeout, info.timeout * 2), true);
            SendHeartbeat();
            pImpl->timer.Start();
        }

        void RoleLeader::Leave()
        {
            pImpl->timer.Stop();
        }

        RPCReply RoleLeader::RPCAppendEntries(const AppendEntriesRPC &message)
        {
            if (message.term > state.currentTerm)
                transformer.TransformSafe(RoleTh::Follower, message.term);
            return RPCReply(state.currentTerm, false);
        }

        RPCReply RoleLeader::RPCRequestVote(const RequestVoteRPC &message)
        {
            if (message.term > state.currentTerm)
                transformer.TransformSafe(RoleTh::Follower, message.term);
            return RPCReply(state.currentTerm, false);
        }

        bool RoleLeader::Put(const string &key, const string &value)
        {
            int size = (int)client.Stubs.size();
            vector<boost::unique_future<pair<RPCReply, bool>>> f;
            for (int i = 0; i < size; ++i)
            {
                Rpc::AppendEntriesMessage message;
                message.set_term(state.currentTerm);
                message.set_leaderid(info.local.ToString());
                message.clear_entries();
                f.push_back(boost::async(move(boost::bind(
                    &Rpc::RaftRpcClient::SendAppendEntries, &client, i, message, true, 11))));
            }
            for (int i = 0; i < size; ++i)
            {
                const auto &result = f[i].get();
                if (result.second)
                {
                }
                else
                {
                }
            }
            //
        }

        pair<bool, string> RoleLeader::Get(const string &key)
        {
            if (state.machine.find(key) == state.machine.end())
                return make_pair(false, "");
            return make_pair(true, state.machine[key]);
        }

        void RoleLeader::SendHeartbeat()
        {
            Rpc::AppendEntriesMessage message;
            message.set_term(state.currentTerm);
            message.set_leaderid(info.local.ToString());
            message.clear_entries();
            int size = (int)client.Stubs.size();
            for (int i = 0; i < size; ++i)
            {
                boost::async(move(boost::bind(
                    &Rpc::RaftRpcClient::SendAppendEntries, &client, i, message, false, 0)));
            }
        }
    }
}
