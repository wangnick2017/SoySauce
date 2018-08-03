//
// Created by wangnick on 7/31/18.
//

#include "RoleBase.h"

namespace Soy
{
    namespace Raft
    {
        RoleBase::RoleBase(State &s, ServerInfo &i, Transformer &t)
            : state(s), info(i), transformer(t)
        {
        }
    }
}
