#pragma once

#include <stdexcept>
#include <string>

namespace filedb {

    class Exception : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    class FileException : public Exception
    {
    public:
        using Exception::Exception;
    };
    class DatabaseException : public Exception
    {
    public:
        using Exception::Exception;
    };

    class ParseException : public Exception
    {
    public:
        using Exception::Exception;
    };

    class ValidationException : public Exception
    {
    public:
        using Exception::Exception;
    };

}