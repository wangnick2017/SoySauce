//
// Created by wangnick on 8/6/18.
//

#include "random.h"
#include <cstdlib>

namespace Soy
{
    std::uint64_t Random(std::uint64_t L, std::uint64_t R)
    {
        return L + std::rand() % (R - L);
    }
}