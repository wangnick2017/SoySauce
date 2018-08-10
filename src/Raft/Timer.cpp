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
            bool repeat;
            boost::thread runningThread;
            function<void()> out = nullptr;
        };

        Timer::Timer(uint64_t p, bool r)
            : pImpl(make_unique<Impl>())
        {
            pImpl->period = p;
            pImpl->repeat = r;
        }

        Timer::~Timer() = default;

        void Timer::Reset(uint64_t p, bool r)
        {
            pImpl->period = p;
            pImpl->repeat = r;
        }

        void Timer::Start()
        {
            pImpl->runningThread = boost::thread([period = pImpl->period, repeat = pImpl->repeat, out = pImpl->out]
            {
                boost::this_thread::disable_interruption di;
                do
                {
                    try
                    {
                        boost::this_thread::restore_interruption ri(di);
                        boost::this_thread::sleep_for(milliseconds(period));
                        out();
                    }
                    catch (boost::thread_interrupted)
                    {
                        return;
                    }
                }
                while (repeat);
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