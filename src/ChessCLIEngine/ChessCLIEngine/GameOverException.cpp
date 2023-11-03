#include "GameOverException.h"

GameOverException::GameOverException(bool isMate)
{
    this->errMsg = "The Game is over: It's " + isMate ? "Checkmate" : "Stalemate";
}

const char* GameOverException::what() const noexcept
{
    return this->errMsg.c_str();
}
