//
// Created by wangnick on 8/4/18.
//

#pragma once

#include "Base.h"
#include "words.hpp"
#include <boost/thread/future.hpp>

namespace Soy
{
    namespace Raft
    {
        enum class TaskType
        {
            TransForm,
            Put,
            Get,
            AppendEntries,
            RequestVote
        };
        struct TaskTransform
        {
            RoleTh newTh;
            Term newTerm;
        };
        struct TaskPut
        {
            std::string key, value;
            boost::promise<bool> &pro;
        };
        struct TaskGet
        {
            std::string key;
            boost::promise<std::pair<bool, std::string>> &pro;
        };
        struct TaskAppendEntries
        {
            AppendEntriesRPC message;
            boost::promise<RPCReply> &pro;
        };
        struct TaskRequestVote
        {
            RequestVoteRPC message;
            boost::promise<RPCReply> &pro;
        };
        class TaskQueue
        {
        public:
            std::queue<TaskType> tasks;
            std::queue<TaskTransform> qTrans;
            std::queue<TaskPut> qPut;
            std::queue<TaskGet> qGet;
            std::queue<TaskAppendEntries> qApp;
            std::queue<TaskRequestVote> qVote;
        };
    }
}
