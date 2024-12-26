#ifndef INVALID_ARGUMENT_EXCEPTION_H
#define INVALID_ARGUMENT_EXCEPTION_H

#include <exception>
#include <string>

class InvalidArgumentException : public std::exception
{
public:
    InvalidArgumentException(std::string reason="Use \"help\" for more information");
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

#endif