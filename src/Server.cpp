//
// Created by wangnick on 7/26/18.
//

#include "Server.h"
#include "ServerInfo.h"
#include "God.h"

using namespace std;

namespace Soy
{
    struct Server::Impl
    {
        Raft::God god;
        ServerInfo info;

        Impl(const string &fileName)
        {
            info.Load(fileName);
        }
    };

    Server::Server(const string &fileName)
        : pImpl(make_unique<Impl>(fileName))
    {
    }

    Server::~Server() = default;

    void Server::Start()
    {
        pImpl->god.Start();
    }

    void Server::Shutdown()
    {
        pImpl->god.Shutdown();
    }
}

