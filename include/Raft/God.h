//
// Created by wangnick on 7/26/18.
//

#pragma once

#include "Role.h"
#include "Base.h"

namespace Soy
{
    namespace Raft
    {
        class God
        {
        public:
            God();
            ~God();
            void Start();
            void Shutdown();
        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
        };
    }
}
