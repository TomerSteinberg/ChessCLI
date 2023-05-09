#include "CommandNotFoundException.h"
#include <iostream>

CommandNotFoundException::CommandNotFoundException(std::string cmd) : _cmd(cmd)
{
    this->errMsg = "Unknown command:'" + this->_cmd + "'. Type help for more information.\n";
}

const char* CommandNotFoundException::what() const noexcept
{
    return this->errMsg.c_str();
}
