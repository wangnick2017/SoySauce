//
// Created by wangnick on 7/25/18.
//

#pragma once

#include "../../Base.h"

namespace Soy::Raft
{
    class ServerStateBase
    {
    public:
        virtual ~ServerStateBase() = default;
        virtual void Init() = 0;
        virtual void Leave() = 0;
    };
}