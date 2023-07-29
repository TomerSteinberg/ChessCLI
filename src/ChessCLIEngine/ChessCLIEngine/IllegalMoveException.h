#include <exception>
#include <iostream>
#include <string>
#pragma once

class IllegalMoveException : public std::exception
{
public:
    IllegalMoveException(std::string reason);
    IllegalMoveException();
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

