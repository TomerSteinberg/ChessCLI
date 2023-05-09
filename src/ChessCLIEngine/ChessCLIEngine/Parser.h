#include "ICommand.h"
#include "CommandFactory.h"


#pragma once
class Parser
{
public:
	static ICommand* parseCommand(std::string cmd);
};

