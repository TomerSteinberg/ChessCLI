#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include <vector>
#include <iostream>	
#include <iomanip>
#include "ICommand.h"
#include "Context.h"


class HelpCommand : public ICommand
{
public:
	HelpCommand(std::vector<std::string> args);

	Result execute(Context& ctx);
	static unsigned int maxArg;

};

#endif
