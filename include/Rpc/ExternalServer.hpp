//
// Created by wangnick on 8/1/18.
//

#pragma once

#include "Base.h"
#include <functional>
#include <thread>
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include "Soy.grpc.pb.h"

namespace Soy
{
    namespace Rpc
    {
        using grpc::ServerBuilder;
        using grpc::ServerContext;
        using grpc::ServerReader;
        using grpc::ServerReaderWriter;
        using grpc::ServerWriter;
        using grpc::Status;
        class ExternalImpl final : public External::Service
        {
        public:
            template <class Func>
            void BindPut(Func &&f)
            {
                put = std::forward<Func>(f);
            }

            template <class Func>
            void BindGet(Func &&f)
            {
                get = std::forward<Func>(f);
            }

            Status Put(ServerContext *context, const PutRequest *request, PutReply *response) override
            {
                put(request->key(), request->value());
                return Status::OK;
            }

            Status Get(ServerContext *context, const GetRequest *request, GetReply *response) override
            {
                response->set_value(get(request->key()));
                return Status::OK;
            }

        private:
            std::function<void(const std::string &, const std::string &)> put;
            std::function<std::string(const std::string &)> get;
        };

        class ExternalServer
        {
        public:
            template <class Func>
            void BindPut(Func &&f)
            {
                impl.BindPut(std::forward<Func>(f));
            }

            template <class Func>
            void BindGet(Func &&f)
            {
                impl.BindGet(std::forward<Func>(f));
            }

            void Start(std::string address)
            {
                ServerBuilder builder;
                builder.AddListeningPort(address, grpc::InsecureServerCredentials());
                builder.RegisterService(&impl);
                server = builder.BuildAndStart();
                runningThread = std::thread([this]
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
            ExternalImpl impl;
            std::unique_ptr<grpc::Server> server;
            std::thread runningThread;
        };
    }
}