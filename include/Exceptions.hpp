#pragma once

#include <string>
#include <exception>

namespace Soy
{
    class Exception : std::exception
    {
    protected:
        const std::string variant;
        std::string detail;
    public:
        Exception(const std::string &v = "", const std::string &d = "")
            : variant(v), detail(d)
        {
        }
        virtual std::string What()
        {
            return variant + " " + detail;
        }
    };
}