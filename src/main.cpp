//
// Created by wangnick on 8/6/18.
//

#include "Client.h"
#include "Server.h"
#include "Base.h"

using namespace Soy;

int main()
{
    std::string fileName;
    std::cin >> fileName;
    Server s(fileName);
    int n;
    while (std::cin >> n)
    {
        if (n == 1)
        {
            s.Start();
        }
        else if (n == 0)
        {
            s.Shutdown();
            break;
        }
    }
    return 0;
}