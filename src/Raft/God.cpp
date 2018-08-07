//
// Created by wangnick on 7/26/18.
//

#include "God.h"
#include "Role.h"
#include "TaskQueue.h"
#include "Transformer.hpp"
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include <grpc++/create_channel.h>
#include "Raft.grpc.pb.h"
#include "ExternalServer.hpp"
#include "RaftRpcServer.hpp"
#include "RaftRpcClient.hpp"

#include <iostream>

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct God::Impl
        {
            ServerInfo &info;
            State state;


            TaskQueue q;
            boost::mutex mut;
            boost::condition_variable cond;
            boost::thread runningThread;
            void Run()
            {
                while (true)
                {
                    auto lock = boost::make_unique_lock(mut);
                    for (; q.tasks.empty();)
                    {
                        cond.wait(lock);
                    }
                    while (!q.tasks.empty())
                    {
                        BOOST_LOG_TRIVIAL(info) << "pop queue tasks:" + to_string((int)q.tasks.front());
                        switch (q.tasks.front())
                        {
                        case TaskType::TransForm:
                            if (th != RoleTh::Dead)
                                roles[(size_t)th]->Leave();
                            if (q.qTrans.front().newTh != RoleTh::Dead)
                            {
                                th = q.qTrans.front().newTh;
                                state.currentTerm = q.qTrans.front().newTerm;
                                roles[(size_t)th]->Init();
                            }
                            q.qTrans.pop();
                            break;
                        case TaskType::Put:
                            q.qPut.front().pro.set_value(roles[(size_t)th]->Put(
                                q.qPut.front().key,
                                q.qPut.front().value));
                            q.qPut.pop();
                            break;
                        case TaskType::Get:
                            q.qGet.front().pro.set_value(roles[(size_t)th]->Get(
                                q.qGet.front().key));
                            q.qGet.pop();
                            break;
                        case TaskType::AppendEntries:
                            q.qApp.front().pro.set_value(roles[(size_t)th]->RPCAppendEntries(
                                q.qApp.front().message));
                            q.qApp.pop();
                            break;
                        case TaskType::RequestVote:
                            q.qVote.front().pro.set_value(roles[(size_t)th]->RPCRequestVote(
                                q.qVote.front().message));
                            q.qVote.pop();
                            break;
                        }
                        q.tasks.pop();
                    }
                }
            }


            Transformer transformer;
            array<unique_ptr<RoleBase>, RoleNumber> roles;
            RoleTh th = RoleTh::Dead;
            void Transform(RoleTh newTh, Term newTerm)
            {
                {
                    auto lock = boost::make_unique_lock(mut);
                    BOOST_LOG_TRIVIAL(info) << "push transform";
                    q.tasks.push(TaskType::TransForm);
                    q.qTrans.push((TaskTransform){newTh, newTerm});
                }
                cond.notify_one();
            }
            void TransformSafe(RoleTh newTh, Term newTerm)
            {
                q.tasks.push(TaskType::TransForm);
                BOOST_LOG_TRIVIAL(info) << "push transformsafe";
                q.qTrans.push((TaskTransform){newTh, newTerm});
            }


            //As a server to Client
            Soy::Rpc::ExternalServer externalServer;
            bool Put(const string &key, const string &value)
            {
                boost::promise<bool> pro;
                {
                    auto lock = boost::make_unique_lock(mut);
                    BOOST_LOG_TRIVIAL(info) << "push put";
                    q.tasks.push(TaskType::Put);
                    q.qPut.push((TaskPut){key, value, pro});
                }
                cond.notify_one();
                return pro.get_future().get();
            }
            pair<bool, string> Get(const string &key)
            {
                boost::promise<pair<bool, std::string>> pro;
                {
                    auto lock = boost::make_unique_lock(mut);
                    BOOST_LOG_TRIVIAL(info) << "push get";
                    q.tasks.push(TaskType::Get);
                    q.qGet.push((TaskGet){key, pro});
                }
                cond.notify_one();
                return pro.get_future().get();
            }


            //As a client
            Rpc::RaftRpcClient raftRpcClient;


            //As a server to Server
            Rpc::RaftRpcServer raftRpcServer;
            RPCReply RPCAppendEntries(const AppendEntriesRPC &message)
            {
                boost::promise<RPCReply> pro;
                {
                    auto lock = boost::make_unique_lock(mut);
                    BOOST_LOG_TRIVIAL(info) << "push append";
                    q.tasks.push(TaskType::AppendEntries);
                    q.qApp.push((TaskAppendEntries){message, pro});
                }
                cond.notify_one();
                return pro.get_future().get();
            }
            RPCReply RPCRequestVote(const RequestVoteRPC &message)
            {
                boost::promise<RPCReply> pro;
                {
                    auto lock = boost::make_unique_lock(mut);
                    BOOST_LOG_TRIVIAL(info) << "push request";
                    q.tasks.push(TaskType::RequestVote);
                    q.qVote.push((TaskRequestVote){message, pro});
                }
                cond.notify_one();
                return pro.get_future().get();
            }

            void Init()
            {
                roles[(size_t)RoleTh::Follower] = make_unique<RoleFollower>(state, info, transformer, raftRpcClient);
                roles[(size_t)RoleTh::Candidate] = make_unique<RoleCandidate>(state, info, transformer, raftRpcClient);
                roles[(size_t)RoleTh::Leader] = make_unique<RoleLeader>(state, info, transformer, raftRpcClient);
                externalServer.BindPut(bind(&God::Impl::Put, this, placeholders::_1, placeholders::_2));
                externalServer.BindGet(bind(&God::Impl::Get, this, placeholders::_1));
                raftRpcServer.BindAppendEntries(bind(&God::Impl::RPCAppendEntries, this, placeholders::_1));
                raftRpcServer.BindRequestVote(bind(&God::Impl::RPCRequestVote, this, placeholders::_1));
                runningThread = boost::thread(bind(&God::Impl::Run, this));
            }

            Impl(ServerInfo &i) : info(i)
            {
                transformer.Bind(
                    bind(&God::Impl::Transform, this, placeholders::_1, placeholders::_2),
                    bind(&God::Impl::TransformSafe, this, placeholders::_1, placeholders::_2));
                for (const auto &srv : info.srvList)
                {
                    raftRpcClient.Stubs.emplace_back(Rpc::RaftRpc::NewStub(
                        grpc::CreateChannel(srv.ToString(), grpc::InsecureChannelCredentials())));
                    state.nextIndex.push_back(0);
                    state.matchIndex.push_back(0);
                }
            }
        };

        God::God(ServerInfo &i)
            : pImpl(make_unique<Impl>(i))
        {
        }

        God::~God() = default;

        void God::Start()
        {
            pImpl->Init();
            pImpl->Transform(RoleTh::Follower, 1);
            pImpl->externalServer.Start(pImpl->info.local.ToString());
            pImpl->raftRpcServer.Start(pImpl->info.local.ToString());
        }

        void God::Shutdown()
        {
            pImpl->externalServer.Shutdown();
            pImpl->raftRpcServer.Shutdown();
            pImpl->runningThread.interrupt();
            pImpl->runningThread.join();
        }
    }
}