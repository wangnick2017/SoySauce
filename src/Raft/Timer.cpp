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
            BOOST_LOG_TRIVIAL(info) << "timer timeset=" + to_string(p);
            pImpl->period = p;
            pImpl->repeat = r;
        }

        void Timer::Start()
        {
            pImpl->runningThread = boost::thread([period = pImpl->period, repeat = pImpl->repeat, out = pImpl->out]
            {
                do
                {
                    try
                    {
                        boost::this_thread::sleep_for(milliseconds(period));
                    }
                    catch (boost::thread_interrupted)
                    {
                        BOOST_LOG_TRIVIAL(info) << "timer interrupted";
                        return;
                    }
                    out();
                    BOOST_LOG_TRIVIAL(info) << "timer no interrupted, go on";
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