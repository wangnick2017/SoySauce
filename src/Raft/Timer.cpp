//
// Created by wangnick on 7/27/18.
//

#include "Timer.h"
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace boost::chrono;

namespace Soy
{
    namespace Raft
    {
        struct Timer::Impl
        {
            uint64_t period;
            boost::thread runningThread;
            function<void()> out = nullptr;
        };

        Timer::Timer(uint64_t p)
            : pImpl(make_unique<Impl>())
        {
            pImpl->period = p;
        }

        Timer::~Timer() = default;

        void Timer::Reset(uint64_t p)
        {
            pImpl->period = p;
        }

        void Timer::Start()
        {
            pImpl->runningThread = boost::thread([period = pImpl->period, out = pImpl->out]
            {
                try
                {
                    boost::this_thread::sleep_for(milliseconds(period));
                }
                catch (boost::thread_interrupted)
                {
                    return;
                }
                out();
            });
        }

        void Timer::Stop()
        {
            pImpl->runningThread.interrupt();
            pImpl->runningThread.join();
        }

        void Timer::Restart()
        {
            Stop();
            Start();
        }

        void Timer::Bind(function<void()> f)
        {
            pImpl->out = std::move(f);
        }
    }
}