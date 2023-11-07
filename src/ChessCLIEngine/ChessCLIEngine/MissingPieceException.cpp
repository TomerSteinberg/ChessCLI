#include "MissingPieceException.h"

MissingPieceException::MissingPieceException(int square, bool color)
{
    std::string side = color ? "white" : "black";
    std::string file = std::to_string(square % 8);
    file[0] += 49;
    this->errMsg = "Illegal move: There is no " + side + " piece on " + file + std::to_string(8 - (square / 8)) + "\n";
}

const char* MissingPieceException::what() const noexcept
{
    return this->errMsg.c_str();
}
