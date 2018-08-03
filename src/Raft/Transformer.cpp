//
// Created by wangnick on 8/3/18.
//

#include "Transformer.h"
#include "State.h"
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>

using namespace boost;

namespace Soy
{
    namespace Raft
    {
        struct Transformer::Impl
        {
            mutex mut;
            condition_variable cond;
            RoleTh th, newTh;
            State state;
            atomic_bool flag{false};

            void Transforming()
            {
                auto lock = make_unique_lock(mut);
                cond.wait(lock, [this]
                {
                    return flag;
                });
                //
            }

            void Notify(RoleTh t, Term newTerm)
            {
                auto lock = make_unique_lock(mut);
                newTh = t;
                state.currentTerm = term;
                flag = true;
                cond.notify_one();
            }
        };

        Transformer::Transformer()
            : pImpl(make_unique<Impl>())
        {
            thread runningThread = thread([]
            {
            });
        }

        Transformer::~Transformer() = default;

        void Transformer::Notify(RoleTh t, Term newTerm)
        {
            pImpl->Notify(t, newTerm);
        }
    }
}