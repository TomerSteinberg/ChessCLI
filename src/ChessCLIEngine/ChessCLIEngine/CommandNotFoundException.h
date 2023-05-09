#pragma once
#include <exception>

class CommandNotFoundException : public std::exception
{
    virtual const char* what() const noexcept;
};

