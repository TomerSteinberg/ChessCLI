#include "CommandNotFoundException.h"

const char* CommandNotFoundException::what() const noexcept
{
    return "Error: Command not found!\n";
}
