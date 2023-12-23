#ifndef EXCEEDED_MAX_ARGUMENTS_EXCPETION_H
#define EXCEEDED_MAX_ARGUMENTS_EXCPETION_H

#include <exception>
#include <string>

class ExceededMaxArgumentsException : public std::exception
{
public:
    ExceededMaxArgumentsException(int recieved, int allowed);
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

#endif