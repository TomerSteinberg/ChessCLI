#pragma once
#include <exception>
#include <string>

class CommandNotFoundException : public std::exception
{
public:
    CommandNotFoundException(std::string cmd);
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

