#ifndef ILLEGAL_MOVE_EXCEPTION_H
#define ILLEGAL_MOVE_EXCEPTION_H

#include <exception>
#include <iostream>
#include <string>

class IllegalMoveException : public std::exception
{
public:
    IllegalMoveException(std::string reason);
    IllegalMoveException();
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

#endif

