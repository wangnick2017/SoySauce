//
// Created by wangnick on 7/26/18.
//

#pragma once

#include "Base.h"

namespace Soy
{
    class ServerID
    {
    };

    class ServerInfo
    {
    public:
        void Load(const std::string &fileName);
        void Save(const std::string &fileName);
    private:
        ServerID local;
        std::vector<ServerID> idList;
        std::uint64_t timeout;
    };
}
