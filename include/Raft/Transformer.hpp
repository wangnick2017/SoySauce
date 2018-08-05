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
            /*RoleTh &th;
            std::array<std::unique_ptr<RoleBase>, RoleNumber> &roles;
            State &state;
        public:
            Transformer(RoleTh &t, std::array<std::unique_ptr<RoleBase>, RoleNumber> &r, State &s)
                : th(t), roles(r), state(s)
            {
            }

            void Transform(RoleTh newTh, Term newTerm)
            {
                if (th != RoleTh::Dead)
                    roles[(size_t)th]->Leave();
                if (newTh != RoleTh::Dead)
                {
                    th = newTh;
                    state.currentTerm = newTerm;
                    roles[(size_t)th]->Init();
                }
            }*/
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