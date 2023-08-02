#pragma once
#include <exception>
#include <string>

class InvalidPromotionException : public std::exception
{
public:
    InvalidPromotionException();
    virtual const char* what() const noexcept;
private:
    std::string errMsg;
};

