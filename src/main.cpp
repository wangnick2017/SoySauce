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
    test();
/*
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
*/
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