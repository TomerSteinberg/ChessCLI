#include "GameOverException.h"

#include <iostream>
GameOverException::GameOverException(bool isMate)
{
    std::string gameOverReason = isMate ? "Checkmate" : "Stalemate";
    this->errMsg = "The Game is over: It's " + gameOverReason;
}

const char* GameOverException::what() const noexcept
{
    return this->errMsg.c_str();
}
