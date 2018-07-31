// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: Raft.proto

#include "Raft.pb.h"
#include "Raft.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace Soy {
namespace Raft {
namespace Rpc {

static const char* RaftRpc_method_names[] = {
  "/Soy.Raft.Rpc.RaftRpc/AppendEntries",
  "/Soy.Raft.Rpc.RaftRpc/RequestVote",
};

std::unique_ptr< RaftRpc::Stub> RaftRpc::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< RaftRpc::Stub> stub(new RaftRpc::Stub(channel));
  return stub;
}

RaftRpc::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_AppendEntries_(RaftRpc_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RequestVote_(RaftRpc_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status RaftRpc::Stub::AppendEntries(::grpc::ClientContext* context, const ::Soy::Raft::Rpc::AppendEntriesMessage& request, ::Soy::Raft::Rpc::Reply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AppendEntries_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::Soy::Raft::Rpc::Reply>* RaftRpc::Stub::AsyncAppendEntriesRaw(::grpc::ClientContext* context, const ::Soy::Raft::Rpc::AppendEntriesMessage& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Soy::Raft::Rpc::Reply>::Create(channel_.get(), cq, rpcmethod_AppendEntries_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::Soy::Raft::Rpc::Reply>* RaftRpc::Stub::PrepareAsyncAppendEntriesRaw(::grpc::ClientContext* context, const ::Soy::Raft::Rpc::AppendEntriesMessage& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Soy::Raft::Rpc::Reply>::Create(channel_.get(), cq, rpcmethod_AppendEntries_, context, request, false);
}

::grpc::Status RaftRpc::Stub::RequestVote(::grpc::ClientContext* context, const ::Soy::Raft::Rpc::RequestVoteMessage& request, ::Soy::Raft::Rpc::Reply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_RequestVote_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::Soy::Raft::Rpc::Reply>* RaftRpc::Stub::AsyncRequestVoteRaw(::grpc::ClientContext* context, const ::Soy::Raft::Rpc::RequestVoteMessage& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Soy::Raft::Rpc::Reply>::Create(channel_.get(), cq, rpcmethod_RequestVote_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::Soy::Raft::Rpc::Reply>* RaftRpc::Stub::PrepareAsyncRequestVoteRaw(::grpc::ClientContext* context, const ::Soy::Raft::Rpc::RequestVoteMessage& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::Soy::Raft::Rpc::Reply>::Create(channel_.get(), cq, rpcmethod_RequestVote_, context, request, false);
}

RaftRpc::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RaftRpc_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< RaftRpc::Service, ::Soy::Raft::Rpc::AppendEntriesMessage, ::Soy::Raft::Rpc::Reply>(
          std::mem_fn(&RaftRpc::Service::AppendEntries), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RaftRpc_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< RaftRpc::Service, ::Soy::Raft::Rpc::RequestVoteMessage, ::Soy::Raft::Rpc::Reply>(
          std::mem_fn(&RaftRpc::Service::RequestVote), this)));
}

RaftRpc::Service::~Service() {
}

::grpc::Status RaftRpc::Service::AppendEntries(::grpc::ServerContext* context, const ::Soy::Raft::Rpc::AppendEntriesMessage* request, ::Soy::Raft::Rpc::Reply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status RaftRpc::Service::RequestVote(::grpc::ServerContext* context, const ::Soy::Raft::Rpc::RequestVoteMessage* request, ::Soy::Raft::Rpc::Reply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace Soy
}  // namespace Raft
}  // namespace Rpc

