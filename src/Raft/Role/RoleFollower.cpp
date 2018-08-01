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

        RoleFollower::~RoleFollower() = default;

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

        bool RoleFollower::Put(const string &key, const string &value)
        {
            return false;
        }

        pair<bool, string> RoleFollower::Get(const string &key)
        {
            return make_pair(false, "");
        }
    }
}