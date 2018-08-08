//
// Created by wangnick on 8/5/18.
//

#pragma once

#include "Base.h"
#include "words.hpp"

namespace Soy
{
    namespace Raft
    {
        class Transformer
        {
        public:
            Transformer()
            {
            }

            template <class Func1, class Func2, class Func3>
            void Bind(Func1 &&t, Func2 &&ts, Func3 &&s)
            {
                Transform = std::forward<Func1>(t);
                TransformSafe = std::forward<Func2>(ts);
                Sender = std::forward<Func3>(s);
            }

            std::function<void(RoleTh, Term)> Transform;
            std::function<void(RoleTh, Term)> TransformSafe;
            std::function<void()> Sender;
        };
    }
}