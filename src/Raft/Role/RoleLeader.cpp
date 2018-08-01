//
// Created by wangnick on 7/26/18.
//

#include "RoleLeader.h"

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct RoleLeader::Impl
        {
            unordered_map<int, Index> nextIndex, matchIndex;
        };

        RoleLeader::RoleLeader()
            : pImpl(make_unique<Impl>())
        {
        }

        RoleLeader::~RoleLeader() = default;

        void RoleLeader::Init()
        {
        }

        void RoleLeader::Leave()
        {
        }

        RPCReply RoleLeader::RPCAppendEntries(const AppendEntriesRPC &message)
        {
        }

        RPCReply RoleLeader::RPCRequestVote(const RequestVoteRPC &message)
        {
        }

        void RoleLeader::Put(const string &key, const string &value)
        {
        }

        string RoleLeader::Get(const string &key)
        {
        }
    }
}
