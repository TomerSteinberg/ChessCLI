#ifndef UNKOWN_COMMAND_EXCEPTION_H
#define UNKOWN_COMMAND_EXCEPTION_H

#include <exception>
#include <string>

class UnkownCommandException : public std::exception
{
public:
    UnkownCommandException(std::string cmd);
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

#endif