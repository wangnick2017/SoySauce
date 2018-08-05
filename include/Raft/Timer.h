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
            Timer(std::uint64_t p = 0, bool r = false);
            ~Timer();
            void Start();
            void Stop();
            void Restart();
            void Reset(std::uint64_t p, bool r = false);
            void Bind(std::function<void()> f);
        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
        };
    }
}
