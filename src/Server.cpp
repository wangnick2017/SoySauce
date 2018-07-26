//
// Created by wangnick on 7/26/18.
//

#include "Server.h"
#include "God.h"

namespace Soy
{
    struct Server::Impl
    {
        Raft::God god;
    };

    Server::Server()
        : pImpl(std::make_unique<Impl>())
    {
    }

    Server::~Server()
    {
    }

    void Server::Start()
    {
    }

    void Server::Shutdown()
    {
    }
}

