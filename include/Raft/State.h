//
// Created by wangnick on 7/27/18.
//

#pragma once

#include "words.h"

namespace Soy
{
    namespace Raft
    {
        class State
        {
            Term currentTerm;
            ServerID votedFor;
        };
    }
}
