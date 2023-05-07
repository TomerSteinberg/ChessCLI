#include "Command.h"
#include "CommandFactory.h"


#pragma once
class Parser
{
public:
	static Command* parseCommand(std::string cmd);
};

