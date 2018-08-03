//
// Created by wangnick on 7/31/18.
//

#pragma once

#include "Base.h"

namespace Soy
{

    class RequestTimeout : public Exception
    {
    };

    class Client
    {
    public:
        Client(const std::string &filename);
        Client(const Client &) = delete;
        Client(Client &&) = delete;
        Client &operator =(const Client &) = delete;
        Client &operator =(Client &&) = delete;
        ~Client();

        void Put(const std::string &key, const std::string &value, std::uint64_t timeout = 5000);
        std::string Get(const std::string &key, std::uint64_t timeout = 5000);

    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };
}
