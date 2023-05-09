#include "CommandNotFoundException.h"
#include <iostream>

CommandNotFoundException::CommandNotFoundException(std::string cmd)
{
    this->errMsg = "Unknown command: '" + cmd + "'. Type help for more information.\n";
}

const char* CommandNotFoundException::what() const noexcept
{
    return this->errMsg.c_str();
}
