#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"

class Context;

class HelpCommand : public ICommand
{
public:
	HelpCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;

};

#endif
