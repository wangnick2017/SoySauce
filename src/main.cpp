//
// Created by wangnick on 8/6/18.
//

#include "Client.h"
#include "Server.h"
#include <iostream>

using namespace Soy;

int main()
{
    std::string fileName;
    std::cin >> fileName;
    Server s(fileName);
    while (true)
    {
        int n;
        std::cin >> n;
        if (n == 1)
            s.Start();
        else if (n == 0)
        {
            s.Shutdown();
            break;
        }
    }
    return 0;
}