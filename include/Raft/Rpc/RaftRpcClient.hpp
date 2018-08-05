//
// Created by wangnick on 8/1/18.
//

#pragma once

#include "Base.h"
#include "words.hpp"
#include <grpc++/create_channel.h>
#include "Raft.grpc.pb.h"

namespace Soy
{
    namespace Raft
    {
        namespace Rpc
        {
            enum class RpcVoteStatus
            {
                Voted,
                Failed,
                ToBeUpdated
            };
            class RaftRpcClient
            {
            public:
                std::vector<std::unique_ptr<Rpc::RaftRpc::Stub>> Stubs;

                void SendAppendEntries()
                {
                }

                std::pair<RpcVoteStatus, Term> SendRequestVote(int sth, const Rpc::RequestVoteMessage &message)
                {
                    grpc::ClientContext ctx;
                    //ctx...
                    Rpc::Reply reply;
                    auto status = Stubs[sth]->RequestVote(&ctx, message, &reply);
                    if (status.ok())
                    {
                        if (reply.ans())
                            return std::make_pair(RpcVoteStatus::Voted, 0);
                        else if (reply.term() > message.term())
                            return std::make_pair(RpcVoteStatus::ToBeUpdated, reply.term());
                    }
                    return std::make_pair(RpcVoteStatus::Failed, 0);
                }
            };
        }
    }
}