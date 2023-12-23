#include "UnkownCommandException.h"

UnkownCommandException::UnkownCommandException(std::string cmd)
{
    this->errMsg = "Unknown command: '" + cmd + "'. Type 'help' for more information.\n";
}

const char* UnkownCommandException::what() const noexcept
{
    return this->errMsg.c_str();
}
