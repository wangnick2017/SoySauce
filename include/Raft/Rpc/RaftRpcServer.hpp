//
// Created by wangnick on 8/1/18.
//

#pragma once

#include "Base.h"
#include "words.hpp"
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include "Raft.grpc.pb.h"

namespace Soy
{
    namespace Raft
    {
        namespace Rpc
        {
            using grpc::Server;
            using grpc::ServerBuilder;
            using grpc::ServerContext;
            using grpc::ServerReader;
            using grpc::ServerReaderWriter;
            using grpc::ServerWriter;
            using grpc::Status;
            class RaftRpcImpl final : public RaftRpc::Service
            {
            public:
                template <class Func>
                void BindAppendEntries(Func &&f)
                {
                    append = std::forward<Func>(f);
                }

                template <class Func>
                void BindRequestVote(Func &&f)
                {
                    vote = std::forward<Func>(f);
                }

                Status AppendEntries(ServerContext* context, const AppendEntriesMessage* request, Reply* response) override
                {
                    RPCReply rpcReply = append(AppendEntriesRPC(
                        request->term(),
                        request->prevlogterm(),
                        request->prevlogindex(),
                        request->leadercommit(),
                        request->leaderid()));
                    response->set_ans(rpcReply.ans);
                    response->set_term(rpcReply.term);
                    return Status::OK;
                }

                Status RequestVote(ServerContext* context, const RequestVoteMessage* request, Reply* response) override
                {
                    RPCReply rpcReply = vote(RequestVoteRPC(
                        request->term(),
                        request->lastlogterm(),
                        request->lastlogindex(),
                        request->candidateid()));
                    response->set_ans(rpcReply.ans);
                    response->set_term(rpcReply.term);
                    return Status::OK;
                }

            private:
                std::function<Raft::RPCReply(const Raft::AppendEntriesRPC &)> append;
                std::function<Raft::RPCReply(const Raft::RequestVoteRPC &)> vote;
            };

            class RaftRpcServer
            {
            public:
                template <class Func>
                void BindAppendEntries(Func &&f)
                {
                    impl.BindAppendEntries(std::forward<Func>(f));
                }

                template <class Func>
                void BindRequestVote(Func &&f)
                {
                    impl.BindRequestVote(std::forward<Func>(f));
                }

                void Start(std::string address)
                {
                    ServerBuilder builder;
                    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
                    builder.RegisterService(&impl);
                    server = builder.BuildAndStart();
                    runningThread = boost::thread([this]
                    {
                        server->Wait();
                    });
                }

                void Shutdown()
                {
                    if (server)
                        server->Shutdown();
                    runningThread.join();
                }

            private:
                RaftRpcImpl impl;
                std::unique_ptr<grpc::Server> server;
                boost::thread runningThread;
            };
        }
    }
}