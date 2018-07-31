//
// Created by wangnick on 7/26/18.
//

#include "God.h"
#include "Role.h"
#include <grpc++/create_channel.h>
#include "Raft.grpc.pb.h"

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
            vector<unique_ptr<Rpc::RaftRpc::Stub>> stubs;

            void Init()
            {
                roles[(size_t)RoleTh::Follower] = make_unique<RoleFollower>();
                roles[(size_t)RoleTh::Candidate] = make_unique<RoleCandidate>();
                roles[(size_t)RoleTh::Leader] = make_unique<RoleLeader>();
                Transform(RoleTh::Follower);
            }

            Impl(ServerInfo &i) : info(i)
            {
                for (const auto &srv : info.srvList)
                {
                    stubs.emplace_back(Rpc::RaftRpc::NewStub(grpc::CreateChannel(
                        srv.ToString(), grpc::InsecureChannelCredentials())));
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
        }

        void God::Shutdown()
        {
        }
    }
}