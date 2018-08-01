//
// Created by wangnick on 7/26/18.
//

#include "RoleCandidate.h"

using namespace std;

namespace Soy
{
    namespace Raft
    {
        struct RoleCandidate::Impl
        {
        };

        RoleCandidate::RoleCandidate()
        {
        }

        RoleCandidate::~RoleCandidate()
        {
        }

        void RoleCandidate::Init()
        {
        }

        void RoleCandidate::Leave()
        {
        }

        RPCReply RoleCandidate::RPCAppendEntries(const AppendEntriesRPC &message)
        {
        }

        RPCReply RoleCandidate::RPCRequestVote(const RequestVoteRPC &message)
        {
        }

        void RoleCandidate::Put(const string &key, const string &value)
        {
        }

        string RoleCandidate::Get(const string &key)
        {
        }
    }
}