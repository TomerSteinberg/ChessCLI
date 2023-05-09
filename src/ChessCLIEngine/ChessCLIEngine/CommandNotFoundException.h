#pragma once
#include <exception>

class CommandNotFoundException : public std::exception
{
public:
    virtual const char* what() const noexcept;
};

