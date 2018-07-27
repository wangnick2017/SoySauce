//
// Created by wangnick on 7/25/18.
//

#pragma once

#include "../../Base.h"

namespace Soy
{
    namespace Raft
    {
        const int RoleNumber = 3;

        enum class RoleTh
        {
            Follower, Candidate, Leader, Dead
        };

        class RoleBase
        {
        public:
            virtual ~RoleBase() = default;
            virtual void Init() = 0;
            virtual void Leave() = 0;
        };
    }
}