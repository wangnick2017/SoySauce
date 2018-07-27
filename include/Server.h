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
        Server(const std::string &fileName);
        ~Server();
        void Start();
        void Shutdown();
    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };
}
