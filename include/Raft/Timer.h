//
// Created by wangnick on 7/27/18.
//

#pragma once

#include "Base.h"

namespace Soy
{
    namespace Raft
    {
        class Timer
        {
        public:
            Timer();
            ~Timer();
        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
        };
    }
}
