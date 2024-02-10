#ifndef CONTINUE_COMMAND_H
#define CONTINUE_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"

#define COMMAND_NAME "continue"

class ContinueCommand : public ICommand
{
public:
	ContinueCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;
};

#endif