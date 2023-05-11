#include <exception>
#include <string>
#pragma once
class ExceededMaxArgumentsException : public std::exception
{
public:
    ExceededMaxArgumentsException(int recieved, int allowed);
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

