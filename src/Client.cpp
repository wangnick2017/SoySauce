//
// Created by wangnick on 7/31/18.
//

#include "Client.h"

#include <boost/atomic.hpp>
#include <boost/chrono.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <grpc++/create_channel.h>
#include "Soy.grpc.pb.h"

using namespace std;
using namespace boost::property_tree;
using namespace boost::chrono;

namespace Soy
{

    struct Client::Impl
    {
        vector<unique_ptr<Rpc::External::Stub>> stubs;
        boost::atomic<size_t> cur{0};
    };

    
    Client::Client(const string &fileName)
        : pImpl(make_unique<Impl>())
    {
        ptree tree;
        read_json(fileName, tree);

        vector<string> srvList;
        for (auto &&srv : tree.get_child("serverList"))
            srvList.emplace_back(srv.second.get_value<string>());

        for (const auto &srv : srvList)
        {
            pImpl->stubs.emplace_back(Rpc::External::NewStub(grpc::CreateChannel(
                srv, grpc::InsecureChannelCredentials())));
        }
    }

    Client::~Client() = default;

    template <class Tp>
    decltype(auto) timeFrom(const Tp &tp)
    {
        return duration_cast<milliseconds>(system_clock::now() - tp).count();
    }

    void Client::Put(const string &key, const string &value, uint64_t timeout)
    {
        auto startTimePoint = system_clock::now();

        while (timeFrom(startTimePoint) <= timeout)
        {
            auto &stub = pImpl->stubs[pImpl->cur % pImpl->stubs.size()];
            grpc::ClientContext ctx;
            ctx.set_deadline(startTimePoint + milliseconds(timeout));
            ctx.set_idempotent(true);

            Rpc::PutRequest request;
            request.set_key(key);
            request.set_value(value);
            Rpc::PutReply reply;
            auto status = stub->Put(&ctx, request, &reply);

            if (status.ok() && reply.status())
                return;
            pImpl->cur++;
        }

        throw RequestTimeout();
    }

    string Client::Get(const string &key, uint64_t timeout)
    {
        auto startTimePoint = system_clock::now();

        while (timeFrom(startTimePoint) <= timeout)
        {
            auto &stub = pImpl->stubs[pImpl->cur % pImpl->stubs.size()];
            grpc::ClientContext ctx;
            ctx.set_deadline(startTimePoint + milliseconds(timeout));
            ctx.set_idempotent(true);

            Rpc::GetRequest request;
            request.set_key(key);
            Rpc::GetReply reply;
            auto status = stub->Get(&ctx, request, &reply);

            if (status.ok() && reply.status())
                return reply.value();
            pImpl->cur++;
        }

        throw RequestTimeout();
    }
}