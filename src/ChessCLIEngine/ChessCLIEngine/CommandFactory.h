#include "ICommand.h"
#include <vector>
#include <unordered_map>
#include "HelpCommand.h"
#include "UnkownCommandException.h"

#pragma once
class CommandFactory
{
public:
	static ICommand* createCommand(std::string cmdName, std::vector<std::string> args);
};

