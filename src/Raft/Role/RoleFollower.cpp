//
// Created by wangnick on 7/26/18.
//

#include "RoleFollower.h"

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct RoleFollower::Impl
        {
        };

        RoleFollower::RoleFollower()
        {
        }

        RoleFollower::~RoleFollower()
        {
        }

        void RoleFollower::Init()
        {
        }

        void RoleFollower::Leave()
        {
        }

        RPCReply RoleFollower::RPCAppendEntries(const AppendEntriesRPC &message)
        {
        }

        RPCReply RoleFollower::RPCRequestVote(const RequestVoteRPC &message)
        {
        }

        void RoleFollower::Put(const string &key, const string &value)
        {
        }

        string RoleFollower::Get(const string &key)
        {
        }
    }
}