//
// Created by wangnick on 7/26/18.
//

#include "God.h"
#include "Role.h"

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct God::Impl
        {
            array<unique_ptr<RoleBase>, RoleNumber> roles;
            RoleTh th = RoleTh::Dead;

            void Init()
            {
                roles[(size_t)RoleTh::Follower] = make_unique<RoleFollower>();
                roles[(size_t)RoleTh::Candidate] = make_unique<RoleCandidate>();
                roles[(size_t)RoleTh::Leader] = make_unique<RoleLeader>();
                Transform(RoleTh::Follower);
            }

            Impl()
            {
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

        God::God()
            : pImpl(make_unique<Impl>())
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