//
// Created by wangnick on 7/25/18.
//

#pragma once

#include "RoleBase.h"

namespace Soy
{
    namespace Raft
    {
        class RoleFollower : public RoleBase
        {
        public:
            RoleFollower();
            ~RoleFollower() override;
            void Init() override;
            void Leave() override;

        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
        };
    }
}

