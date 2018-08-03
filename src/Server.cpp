//
// Created by wangnick on 7/26/18.
//

#include <cstdlib>
#include <ctime>
#include "Server.h"
#include "ServerInfo.h"
#include "God.h"

using namespace std;

namespace Soy
{
    struct Server::Impl
    {
        ServerInfo info;
        Raft::God god;

        Impl(const string &fileName)
            : info(fileName), god(info)
        {
        }
    };

    Server::Server(const string &fileName)
        : pImpl(make_unique<Impl>(fileName))
    {
    }

    Server::~Server() = default;

    void Server::Start()
    {
        srand(time(NULL));
        pImpl->god.Start();
    }

    void Server::Shutdown()
    {
        pImpl->god.Shutdown();
    }
}

