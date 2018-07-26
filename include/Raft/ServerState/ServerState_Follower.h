//
// Created by wangnick on 7/25/18.
//

#pragma once

#include "ServerState_Base.h"

namespace Soy::Raft
{
    class ServerStateFollower : public ServerStateBase
    {
    public:
        ServerStateFollower();
        ~ServerStateFollower() override;
        void Init() override;
        void Leave() override;

    private:
        struct Impl;
        std::unique_ptr<impl> pImpl;
    };
}

