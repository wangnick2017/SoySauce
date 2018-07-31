//
// Created by wangnick on 7/26/18.
//

#pragma once

#include "Role.h"
#include "Base.h"
#include "ServerInfo.h"

namespace Soy
{
    namespace Raft
    {
        class God
        {
        public:
            God(ServerInfo &i);
            ~God();
            void Start();
            void Shutdown();
        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
        };
    }
}
