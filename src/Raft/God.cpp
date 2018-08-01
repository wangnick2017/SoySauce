//
// Created by wangnick on 7/26/18.
//

#include "God.h"
#include "Role.h"
#include <grpc++/create_channel.h>
#include "Raft.grpc.pb.h"
#include "ExternalServer.hpp"
#include "RaftRpcServer.hpp"
#include "RaftRpcClient.hpp"

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct God::Impl
        {
            ServerInfo &info;

            array<unique_ptr<RoleBase>, RoleNumber> roles;
            RoleTh th = RoleTh::Dead;


            //As a server to Client
            Soy::Rpc::ExternalServer externalServer;
            bool Put(const string &key, const string &value)
            {
                return roles[(size_t)th]->Put(key, value);
            }
            pair<bool, string> Get(const string &key)
            {
                return roles[(size_t)th]->Get(key);
            }


            //As a client
            Rpc::RaftRpcClient raftRpcClient;


            //As a server to Server
            Rpc::RaftRpcServer raftRpcServer;
            RPCReply RPCAppendEntries(const AppendEntriesRPC &message)
            {
                return roles[(size_t)th]->RPCAppendEntries(message);
            }
            RPCReply RPCRequestVote(const RequestVoteRPC &message)
            {
                return roles[(size_t)th]->RPCRequestVote(message);
            }

            void Init()
            {
                roles[(size_t)RoleTh::Follower] = make_unique<RoleFollower>();
                roles[(size_t)RoleTh::Candidate] = make_unique<RoleCandidate>();
                roles[(size_t)RoleTh::Leader] = make_unique<RoleLeader>();
                Transform(RoleTh::Follower);
                externalServer.BindPut(bind(&God::Impl::Put, this, placeholders::_1, placeholders::_2));
                externalServer.BindGet(bind(&God::Impl::Get, this, placeholders::_1));
                raftRpcServer.BindAppendEntries(bind(&God::Impl::RPCAppendEntries, this, placeholders::_1));
                raftRpcServer.BindRequestVote(bind(&God::Impl::RPCRequestVote, this, placeholders::_1));
            }

            Impl(ServerInfo &i) : info(i)
            {
                for (const auto &srv : info.srvList)
                {
                    raftRpcClient.Stubs.emplace_back(Rpc::RaftRpc::NewStub(
                        grpc::CreateChannel(srv.ToString(), grpc::InsecureChannelCredentials())));
                }
            }

            void Transform(RoleTh target)
            {
                if (th != RoleTh::Dead)
                {
                    roles[(size_t)th]->Leave();
                }
                if (target != RoleTh::Dead)
                {
                    th = target;
                    roles[(size_t)th]->Init();
                }
            }
        };

        God::God(ServerInfo &i)
            : pImpl(make_unique<Impl>(i))
        {
        }

        God::~God() = default;

        void God::Start()
        {
            pImpl->Init();
            pImpl->externalServer.Start(pImpl->info.local.ToString());
            pImpl->raftRpcServer.Start(pImpl->info.local.ToString());
        }

        void God::Shutdown()
        {
            pImpl->externalServer.Shutdown();
            pImpl->raftRpcServer.Shutdown();
        }
    }
}