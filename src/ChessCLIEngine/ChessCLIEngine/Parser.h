#include "ICommand.h"
#include "CommandFactory.h"
#include <sstream>
#include <iostream>
#include "UnkownCommandException.h"

#pragma once
class Parser
{
public:
	static std::unique_ptr<ICommand> parseCommand(std::string cmd);
private:
	static std::vector<std::string> splitBySpace(std::string cmd);
};

