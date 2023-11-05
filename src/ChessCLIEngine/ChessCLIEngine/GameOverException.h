#ifndef GAME_OVER_EXCEPTION_H
#define GAME_OVER_EXCEPTION_H


#include <exception>
#include <string>

class GameOverException : public std::exception
{
public:
    GameOverException(bool isMate);
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

#endif