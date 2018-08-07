//
// Created by wangnick on 7/26/18.
//

#include "ServerInfo.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/typeof/typeof.hpp>

using namespace std;
using namespace boost::property_tree;

namespace Soy
{
    ServerID::ServerID(const string &s)
    {
        if (s.empty())
        {
            address = "";
            port = 0;
            return;
        }
        size_t c = s.find(':');
        if (c == string::npos)
            throw Exception("Error ID");
        address = move(s.substr(0, c));
        port = (Port)stoul(s.substr(c + 1));
    }

    string ServerID::ToString() const
    {
        if (address.empty())
            return "";
        return address + ":" + to_string(port);
    }

    ServerInfo::ServerInfo(const string &fileName)
    {
        ptree tree;
        read_json(fileName, tree);
        local = ServerID(tree.get<string>("localAddress"));
        updateTimeout = tree.get<uint64_t>("updateTimeout");
        electionTimeout = tree.get<uint64_t>("electionTimeout");
        heartbeatTimeout = tree.get<uint64_t>("heartbeatTimeout");
        for (auto &&server : tree.get_child("serverList"))
            srvList.emplace_back(server.second.get_value<string>());
    }

    void ServerInfo::Save(const string &fileName)
    {
        ptree tree;
        tree.put("localAddress", local.ToString());
        tree.put("updateTimeout", updateTimeout);
        tree.put("electionTimeout", electionTimeout);
        tree.put("heartbeatTimeout", heartbeatTimeout);
        ptree jsonList;
        for (auto &&srv : srvList)
        {
            ptree server;
            server.put("", srv.ToString());
            jsonList.push_back(make_pair("", server));
            tree.put("serverList.serverId", srv.ToString());
        }
        tree.add_child("serverList", jsonList);
        write_json(fileName, tree);
    }
}