#include <exception>
#include <iostream>
#include <string>
#pragma once

class MissingPieceException : public std::exception
{
public:
    MissingPieceException(int square, bool color);
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

