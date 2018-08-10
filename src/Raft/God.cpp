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

#include <fstream>

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct God::Impl
        {
            ServerInfo &info;
            State state;

            void ReadConfig()
            {
                ifstream fin("config-" + info.localRaft.ToString());
                if (fin.is_open())
                {
                    fin >> state.currentTerm;
                    string sa, sb;
                    fin >> sa;
                    state.votedFor =  ServerID(sa);
                    Term et;
                    while (fin >> et)
                    {
                        fin >> sa >> sb;
                        state.log.emplace_back((Entry){sa, sb, et});
                    }
                }
                else
                    state.currentTerm = 1;
                fin.close();
            }
            void SaveConfig()
            {
                ofstream fout("config-" + info.localRaft.ToString());
                if (fout.is_open())
                {
                    fout << state.currentTerm << endl << state.votedFor.ToString() << endl;
                    for (int i = 0, j = state.log.size(); i < j; ++i)
                        fout << state.log[i].term << " " << state.log[i].op << " " << state.log[i].arg << endl;
                }
                fout.close();
            }


            TaskQueue q;
            boost::mutex mut;
            boost::condition_variable cond;
            boost::thread runningThread;
            void Run()
            {
                while (true)
                {
                    auto lock = boost::make_unique_lock(mut);
                    cond.wait(lock, [this]
                    {
                        return !q.tasks.empty();
                    });
                    while (!q.tasks.empty())
                    {
                        switch (q.tasks.front())
                        {
                        case TaskType::TransForm:
                        {
                            const auto &t = q.qTrans.front();
                            if (th != RoleTh::Dead)
                                roles[(size_t)th]->Leave();
                            if (t.newTh != RoleTh::Dead)
                            {
                                if (th != t.newTh)
                                    state.currentTerm = t.newTerm;
                                else
                                    ++state.currentTerm;
                                th = t.newTh;
                                roles[(size_t)th]->Init();
                            }
                            q.qTrans.pop();
                            break;
                        }
                        case TaskType::Put:
                        {
                            const auto &t = q.qPut.front();
                            q.qPut.front().pro.set_value(roles[(size_t)th]->Put(
                                q.qPut.front().key,
                                q.qPut.front().value));
                            q.qPut.pop();
                            SaveConfig();
                            break;
                        }
                        case TaskType::Get:
                        {
                            const auto &t = q.qGet.front();
                            t.pro.set_value(roles[(size_t)th]->Get(t.key));
                            q.qGet.pop();
                            break;
                        }
                        case TaskType::AppendEntries:
                        {
                            const auto &t = q.qApp.front();
                            t.pro.set_value(roles[(size_t)th]->RPCAppendEntries(t.message));
                            q.qApp.pop();
                            SaveConfig();
                            break;
                        }
                        case TaskType::RequestVote:
                        {
                            const auto &t = q.qVote.front();
                            t.pro.set_value(roles[(size_t)th]->RPCRequestVote(t.message));
                            q.qVote.pop();
                            SaveConfig();
                            break;
                        }
                        case TaskType::SendHeartbeat:
                            if (th == RoleTh::Leader)
                            {
                                roles[(size_t)th]->SendHeartbeat();
                            }
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
                    q.tasks.push(TaskType::TransForm);
                    q.qTrans.push((TaskTransform){newTh, newTerm});
                }
                cond.notify_one();
            }
            void TransformSafe(RoleTh newTh, Term newTerm)
            {
                q.tasks.push(TaskType::TransForm);
                q.qTrans.push((TaskTransform){newTh, newTerm});
            }
            void Sender()
            {
                {
                    auto lock = boost::make_unique_lock(mut);
                    q.tasks.push(TaskType::SendHeartbeat);
                }
                cond.notify_one();
            }


            //As a server to Client
            Soy::Rpc::ExternalServer externalServer;
            bool Put(const string &key, const string &value)
            {
                boost::promise<bool> pro;
                {
                    auto lock = boost::make_unique_lock(mut);
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
                    bind(&God::Impl::TransformSafe, this, placeholders::_1, placeholders::_2),
                    bind(&God::Impl::Sender, this));
                for (int i = 0, j = info.raftServers.size(); i < j; ++i)
                {
                    string s = info.raftServers[i].ToString();
                    if (s == info.localRaft.ToString())
                        raftRpcClient.LocalNumber = i;
                    raftRpcClient.Stubs.emplace_back(Rpc::RaftRpc::NewStub(
                        grpc::CreateChannel(s, grpc::InsecureChannelCredentials())));
                    state.nextIndex.push_back(0);
                    state.matchIndex.push_back(-1);
                }
                state.currentTerm = 1;
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
            pImpl->th = RoleTh::Follower;
            pImpl->roles[(size_t)pImpl->th]->Init();
            pImpl->externalServer.Start(pImpl->info.localExternal.ToString());
            pImpl->raftRpcServer.Start(pImpl->info.localRaft.ToString());
        }

        void God::Restart()
        {
            pImpl->ReadConfig();
            pImpl->Init();
            pImpl->th = RoleTh::Follower;
            pImpl->roles[(size_t)pImpl->th]->ReInit(pImpl->state.currentTerm, pImpl->state.votedFor.ToString());
            pImpl->externalServer.Start(pImpl->info.localExternal.ToString());
            pImpl->raftRpcServer.Start(pImpl->info.localRaft.ToString());
        }

        void God::Shutdown()
        {
            pImpl->externalServer.Shutdown();
            pImpl->raftRpcServer.Shutdown();
            if (pImpl->th != RoleTh::Dead)
                pImpl->roles[(size_t)pImpl->th]->Leave();
            pImpl->runningThread.interrupt();
            pImpl->runningThread.join();
        }
    }
}