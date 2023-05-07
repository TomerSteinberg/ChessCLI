#include "CommandFactory.h"

std::unique_ptr<Command> CommandFactory::createCommand(std::string cmdName, std::vector<std::string> args)
{
    return std::unique_ptr<Command>();
}
