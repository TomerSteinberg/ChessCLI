#include "MissingPieceException.h"

MissingPieceException::MissingPieceException(int square, bool color)
{
    std::string side = color ? "white" : "black";
    this->errMsg = "Illegal move: There is no " + side + " piece on " + std::to_string(square);
}

const char* MissingPieceException::what() const noexcept
{
    return this->errMsg.c_str();
}
