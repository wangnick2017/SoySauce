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
            Transformer(std::function<void(RoleTh, Term)> t)
                : Transform(std::move(t))
            {
            }

            std::function<void(RoleTh, Term)> Transform;
        };
    }
}