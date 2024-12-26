#include "InvalidCommandException.h"

InvalidCommandException::InvalidCommandException(std::string cmdType)
{
    this->errMsg = "Invalid Command: Can't run '" + cmdType + "' without a loaded game instance\n";
}

const char* InvalidCommandException::what() const noexcept
{
    return this->errMsg.c_str();
}
