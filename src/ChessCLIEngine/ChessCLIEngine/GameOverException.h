#include <exception>
#include <string>
#pragma once
class GameOverException : public std::exception
{
public:
    GameOverException(bool isMate);
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

