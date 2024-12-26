#ifndef MISSING_PIECE_EXCEPTION_H
#define MISSING_PIECE_EXCEPTION_H

#include <exception>
#include <iostream>
#include <string>


class MissingPieceException : public std::exception
{
public:
    MissingPieceException(int square, bool color);
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

#endif