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
            BOOST_LOG_TRIVIAL(info) << "start ok";
        }
        else if (n == 0)
        {
            s.Shutdown();
            break;
        }
    }
    BOOST_LOG_TRIVIAL(info) << "bye bye";

/*
    std::string fileName, a, b;
    std::cin >> fileName;
    Client c(fileName);
    int n;
    while (std::cin >> n)
    {
        if (n == 1)
        {
            std::cin >> a >> b;
            c.Put(a, b, 8000);
        }
        else if (n == 2)
        {
            std::cin >> a;
            std::cout << c.Get(a) << std::endl;
        };
    }
*/
    return 0;
}