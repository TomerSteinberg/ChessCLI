#ifndef INVALID_PROMOTION_EXCEPTION_H
#define INVALID_PROMOTION_EXCEPTION_H

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

#endif