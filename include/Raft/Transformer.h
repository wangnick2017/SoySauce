//
// Created by wangnick on 8/3/18.
//

#pragma once

#include "words.hpp"

namespace Soy
{
    namespace Raft
    {
        class Transformer
        {
        public:
            Transformer();
            ~Transformer();
            void Notify(RoleTh t, Term newTerm);

        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl;
        };
    }
}
