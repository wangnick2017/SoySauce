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
            pImpl->runningThread = boost::thread([]
            {
                try
                {
                    boost::this_thread::sleep_for(duration_cast<milliseconds>(pImpl->period));
                }
                catch (boost::thread_interrupted)
                {
                    //need to be completed
                    return;
                }
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
    }
}