//
// Created by wangnick on 7/26/18.
//

#pragma once

#include "Base.h"

namespace Soy
{
    class Server
    {
    public:
        Server();
        ~Server();
        Start();
        Shutdown();
    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };
}
