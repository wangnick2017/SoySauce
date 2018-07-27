//
// Created by wangnick on 7/26/18.
//

#include "ServerInfo.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;

namespace Soy
{
    ServerID::ServerID(const string &s)
    {
        if (s.empty())
            return;
        size_t c = s.find(':');
        if (c == string::npos)
            throw Exception("Error ID");
        address = move(s.substr(0, c));
        port = stoul(s.substr(c + 1));
    }

    string ServerID::ToString() const
    {
        return address + ":" + to_string(port);
    }

    void ServerInfo::Load(const string &fileName)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::read_json(fileName, tree);
        local = ServerID(tree.get<string>("localAddress"));
        timeout = tree.get<uint64_t>("timeout");
        for (auto &&server : tree.get_child("serverList"))
            idList.emplace_back(server.second.get_value<string>());
    }

    void ServerInfo::Save(const string &fileName)
    {
        boost::property_tree::ptree tree;
        tree.put("localAddress", local.ToString());
        tree.put("timeout", timeout);
        boost::property_tree::ptree jsonList;
        for (auto &&id : idList)
        {
            boost::property_tree::ptree server;
            server.put("", id.ToString());
            jsonList.push_back(make_pair("", server));
            tree.put("serverList.serverId", id.ToString());
        }
        tree.add_child("serverList", jsonList);
        boost::property_tree::write_json(fileName, tree);
    }
}