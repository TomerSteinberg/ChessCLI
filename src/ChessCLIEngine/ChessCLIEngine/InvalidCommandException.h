#ifndef INVALID_COMMAND_EXCEPTION_H
#define INVALID_COMMAND_EXCEPTION_H

#include <exception>
#include <string>

class InvalidCommandException : public std::exception
{
public:
    InvalidCommandException(std::string cmdType);
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

#endif