//
// Created by wangnick on 7/31/18.
//

#include "RoleBase.h"

namespace Soy
{
    namespace Raft
    {
        RoleBase::RoleBase(State &s, ServerInfo &i, Transformer &t, Rpc::RaftRpcClient &c)
            : state(s), info(i), transformer(t), client(c)
        {
        }

        void RoleBase::SendHeartbeat()
        {
        }
    }
}
