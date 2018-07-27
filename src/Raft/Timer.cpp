//
// Created by wangnick on 7/27/18.
//

#include "Timer.h"

namespace Soy
{
    namespace Raft
    {
        struct Timer::Impl
        {
        };

        Timer::Timer()
            : pImpl(make_unique<Impl>())
        {
        }

        Timer::~Timer() = default;
    }
}