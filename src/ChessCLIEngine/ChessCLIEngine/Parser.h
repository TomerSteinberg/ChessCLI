#include "ICommand.h"
#include "CommandFactory.h"
#include <sstream>
#include <iostream>
#include "CommandNotFoundException.h"

#pragma once
class Parser
{
public:
	static ICommand* parseCommand(std::string cmd);
private:
	static std::vector<std::string> splitBySpace(std::string cmd);
};

