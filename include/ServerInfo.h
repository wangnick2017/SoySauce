//
// Created by wangnick on 7/26/18.
//

#pragma once

#include "Base.h"

namespace Soy
{
    using Port = std::uint16_t;

    class ServerID
    {
    public:
        ServerID(const std::string &s = "");
        std::string ToString() const;
    private:
        std::string address;
        Port port;
    };

    struct ServerInfo
    {
        ServerInfo(const std::string &fileName);
        void Save(const std::string &fileName);
        ServerID local;
        std::vector<ServerID> srvList;
        std::uint64_t timeout;
    };
}
