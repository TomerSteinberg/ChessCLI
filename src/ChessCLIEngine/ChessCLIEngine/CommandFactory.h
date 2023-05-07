#include "Command.h"
#include <vector>

#pragma once
class CommandFactory
{
	static Command* createCommand(std::string cmdName, std::vector<std::string> args);
};

