#include "ICommand.h"
#include <vector>
#include <unordered_map>

#include "UnkownCommandException.h"

#include "HelpCommand.h"
#include "ClearCommand.h"
#include "QuitCommand.h"


#pragma once
class CommandFactory
{
public:
	static std::unique_ptr<ICommand> createCommand(std::string cmdName, std::vector<std::string> args);
};

