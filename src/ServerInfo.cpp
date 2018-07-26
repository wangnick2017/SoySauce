//
// Created by wangnick on 7/26/18.
//

#include "ServerInfo.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;

namespace Soy
{
    void ServerInfo::Load(const string &fileName)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::read_json(fileName, tree);
        local = ServerId(tree.get<string>("localAddress"));
        timeout = tree.get<uint64_t>("electionTimeout");
        for (auto &&server : tree.get_child("serverList"))
            idList.emplace_back(server.second.get_value<string>());
    }

    void ServerInfo::save(const string &fileName)
    {
        boost::property_tree::ptree tree;
        tree.put("localAddress", local.toString());
        tree.put("electionTimeout", timeout);
        boost::property_tree::ptree jsonList;
        for (auto &&id : idList)
        {
            boost::property_tree::ptree server;
            server.put("", id.toString());
            jsonList.push_back(make_pair("", srv));
            tree.put("serverList.serverId", id.toString());
        }
        tree.add_child("serverList", jsonList);
        boost::property_tree::write_json(fileName, tree);
    }
}