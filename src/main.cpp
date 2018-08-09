//
// Created by wangnick on 8/6/18.
//

#include <thread>

#include "Client.h"
#include "Server.h"
#include "Base.h"
#include <boost/thread.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace logging=boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;


using namespace Soy;

void test()
{
    Server s1("s1.json");
    Server s2("s2.json");
    Server s3("s3.json");
    s1.Start();
    s2.Start();
    s3.Start();
    while (true)
        std::this_thread::yield();
}

int main()
{
    /*
    logging::add_file_log("sample.log");
    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
    test();
    boost::thread t1(test, "s1.json");
    boost::thread t2(test, "s2.json");
    boost::thread t3(test, "s3.json");
    t1.join();
    t2.join();
    t3.join();
*/
    //test();

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
    Client c("s.json");
    int n;
    while (std::cin >> n)
    {
        if (n == 1)
        {
            std::cin >> a >> b;
            c.Put(a, b, 4000);
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

/*
#include <algorithm>
#include <iostream>
#include <boost/chrono/duration.hpp>
#include <boost/thread/thread.hpp>
#include <ctime>

#include "Server.h"
#include "Client.h"

#include <random>
#include <thread>
#include <atomic>

template <class T> T intRand(T lb, T ub) {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 generator(rd());
    std::uniform_int_distribution<T> distribution(lb, ub);
    return distribution(generator);
}

using namespace Soy;

int main() {
    using namespace std::chrono_literals;

    srand(time(nullptr));
    Server s1("s1.json");
    Server s2("s2.json");
    Server s3("s3.json");
    s1.Start();
    s2.Start();
    s3.Start();
    //while (true)
    //    std::this_thread::yield();
//  server2.shutdown();
//  server3.shutdown();

    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    std::string filename4 = "s.json";
    Client client(filename4);

    std::vector<std::thread> ts;
    for (char ch = 'a'; ch <= 'o'; ++ch) {
        ts.emplace_back(std::thread([ch, &client] {
            std::this_thread::sleep_for(std::chrono::milliseconds(intRand(30, 50)));
            std::string key = {ch};
            std::string val = {(char)std::toupper(ch)};
            client.Put(key, val, 50);
        }));
    }
    for (auto &t : ts)
        t.join();

//  server2.start();
//  server3.start();

    std::atomic<int> fucked{0};

    std::this_thread::sleep_for(2s);
    ts.clear();
    for (char ch = 'a'; ch <= 'o'; ++ch) {
        ts.emplace_back(std::thread([ch, &client, &fucked] {
            std::this_thread::sleep_for(std::chrono::milliseconds(intRand(30, 50)));
            std::string key = {ch};
            std::string ans = {(char)std::toupper(ch)};
            try {
                auto val = client.Get(key, 50);
                if (val != ans)
                    throw ;
            } catch (...) {
                ++fucked;
            }
        }));
    }
    for (auto &t : ts)
        t.join();

    //    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    //    boost::thread t1(std::bind(&Client::Put, &client, "LZY", "DAZHAOGE",
    //    5000)); t1.join(); boost::thread t2(std::bind(&Client::Get, &client,
    //    "LZY", 5000)); t2.join(); boost::thread t3(std::bind(&Client::Put,
    //    &client, "QSC", "DANIUGE", 5000)); t3.join(); boost::thread
    //    t4(std::bind(&Client::Get, &client, "QSC", 5000)); t4.join();
    //    boost::thread t5(std::bind(&Client::Put, &client, "RYW", "DABAOGE",
    //    5000)); t5.join(); boost::thread t6(std::bind(&Client::Get, &client,
    //    "RYW", 5000)); t6.join();

    s1.Shutdown();
    s2.Shutdown();
    s3.Shutdown();

    std::cout << "fucked = " << fucked << std::endl;

    /*server3.shutdown();
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    server3.restart();
    boost::this_thread::sleep_for(boost::chrono::seconds(2));*/
/*
    return 0;
}
*/