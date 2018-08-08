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
                int LocalNumber;

                std::pair<RPCReply, bool> SendAppendEntries(
                    int sth,
                    const Rpc::AppendEntriesMessage &m,
                    bool repeat = false,
                    std::uint64_t timeout = 0)
                {
                    Rpc::AppendEntriesMessage message{m};
                    auto startTimePoint = boost::chrono::system_clock::now();
                    do
                    {
                        grpc::ClientContext ctx;
                        ctx.set_deadline(std::chrono::system_clock::now()+std::chrono::milliseconds(broadcastTimeout));
                        Rpc::Reply reply;
                        //BOOST_LOG_TRIVIAL(info) << "hahaha";
                        auto status = Stubs[sth]->AppendEntries(&ctx, message, &reply);
                        if (status.ok())
                            return std::make_pair(RPCReply(reply.term(), reply.ans()), status.ok());
                        else
                            BOOST_LOG_TRIVIAL(info) << status.error_message();
                        //BOOST_LOG_TRIVIAL(info) << "hehehe";
                    }
                    while (repeat && timeFrom(startTimePoint) <= timeout);
                    return std::make_pair(RPCReply(0, false), false);
                }

                std::pair<RPCReply, bool> SendRequestVote(int sth, const Rpc::RequestVoteMessage &message)
                {
                    grpc::ClientContext ctx;
                    ctx.set_deadline(std::chrono::system_clock::now()+std::chrono::milliseconds(broadcastTimeout));
                    Rpc::Reply reply;
                    //BOOST_LOG_TRIVIAL(info) << "aaaaaaaaaaaaaaaaaaaaaaa?";
                    auto status = Stubs[sth]->RequestVote(&ctx, message, &reply);
                    //BOOST_LOG_TRIVIAL(info) << "bbbbbbbbbbbbbbbbbbbbbbb.";
                    if (!status.ok())
                        BOOST_LOG_TRIVIAL(info) << (int)status.error_code();
                    return std::make_pair(RPCReply(reply.term(), reply.ans()), status.ok());
                }
            };
        }
    }
}