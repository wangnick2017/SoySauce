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
        Server(const Server &) = delete;
        Server(Server &&) = delete;
        Server &operator =(const Server &) = delete;
        Server &operator =(Server &&) = delete;
        ~Server();
        void Start();
        void Shutdown();
        void Restart();
    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };
}
