#include "InvalidArgumentException.h"

InvalidArgumentException::InvalidArgumentException(std::string reason)
{
    this->errMsg = "Invalid Argument: " + reason + "\n";
}

const char* InvalidArgumentException::what() const noexcept
{
    return this->errMsg.c_str();
}
