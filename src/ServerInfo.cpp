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
        localExternal = ServerID(tree.get<string>("localExternalAddress"));
        localRaft = ServerID(tree.get<string>("localRaftAddress"));
        updateTimeout = tree.get<uint64_t>("updateTimeout");
        electionTimeout = tree.get<uint64_t>("electionTimeout");
        heartbeatTimeout = tree.get<uint64_t>("heartbeatTimeout");
        for (auto &&server : tree.get_child("ExternalServerList"))
            externalServers.emplace_back(server.second.get_value<string>());
        for (auto &&server : tree.get_child("RaftServerList"))
            raftServers.emplace_back(server.second.get_value<string>());
    }

    void ServerInfo::Save(const string &fileName)
    {
        ptree tree;
        tree.put("localExternalAddress", localExternal.ToString());
        tree.put("localRaftAddress", localRaft.ToString());
        tree.put("updateTimeout", updateTimeout);
        tree.put("electionTimeout", electionTimeout);
        tree.put("heartbeatTimeout", heartbeatTimeout);
        ptree jsonList;
        for (auto &&srv : externalServers)
        {
            ptree server;
            server.put("", srv.ToString());
            jsonList.push_back(make_pair("", server));
            tree.put("ExternalServerList.serverId", srv.ToString());
        }
        tree.add_child("ExternalServerList", jsonList);
        ptree jsonList2;
        for (auto &&srv : raftServers)
        {
            ptree server;
            server.put("", srv.ToString());
            jsonList2.push_back(make_pair("", server));
            tree.put("RaftServerList.serverId", srv.ToString());
        }
        tree.add_child("RaftServerList", jsonList2);
        write_json(fileName, tree);
    }
}