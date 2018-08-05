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

            template <class Func1, class Func2>
            void Bind(Func1 &&t, Func2 &&ts)
            {
                Transform = std::forward<Func1>(t);
                TransformSafe = std::forward<Func2>(ts);
            }

            std::function<void(RoleTh, Term)> Transform;
            std::function<void(RoleTh, Term)> TransformSafe;
        };
    }
}