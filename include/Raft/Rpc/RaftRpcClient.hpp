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
            class RaftRpcClient
            {
            public:
                std::vector<std::unique_ptr<Rpc::RaftRpc::Stub>> Stubs;
                void SendAppendEntries()
                {
                    for (int i = 0, j = Stubs.size(); i < j; ++i)
                    {
                        //std::async(std::launch::async, test, s[i-1]);
                    }
                }
                void SendRequestVote()
                {
                }
            };
        }
    }
}