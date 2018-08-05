//
// Created by wangnick on 8/1/18.
//

#pragma once

#include "Base.h"
#include "words.hpp"
#include <boost/chrono.hpp>
#include <grpc++/create_channel.h>
#include "Raft.grpc.pb.h"

namespace Soy
{
    namespace Raft
    {
        namespace Rpc
        {
            template <class Tp>
            decltype(auto) timeFrom(const Tp &tp)
            {
                return boost::chrono::duration_cast<boost::chrono::milliseconds>
                    (boost::chrono::system_clock::now() - tp).count();
            }
            class RaftRpcClient
            {
            public:
                std::vector<std::unique_ptr<Rpc::RaftRpc::Stub>> Stubs;

                std::pair<RPCReply, bool> SendAppendEntries(
                    int sth,
                    const Rpc::AppendEntriesMessage &message,
                    bool repeat = false,
                    std::uint64_t timeout = 0)
                {
                    auto startTimePoint = boost::chrono::system_clock::now();
                    do
                    {
                        grpc::ClientContext ctx;
                        //ctx...
                        Rpc::Reply reply;
                        auto status = Stubs[sth]->AppendEntries(&ctx, message, &reply);
                        if (status.ok())
                            return std::make_pair(RPCReply(reply.term(), reply.ans()), status.ok());
                    }
                    while (repeat && timeFrom(startTimePoint) <= timeout);
                    return std::make_pair(RPCReply(0, false), false);
                }

                std::pair<RPCReply, bool> SendRequestVote(int sth, const Rpc::RequestVoteMessage &message)
                {
                    grpc::ClientContext ctx;
                    //ctx...
                    Rpc::Reply reply;
                    auto status = Stubs[sth]->RequestVote(&ctx, message, &reply);
                    return std::make_pair(RPCReply(reply.term(), reply.ans()), status.ok());
                }
            };
        }
    }
}