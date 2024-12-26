#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"


#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "exit"


class ExitCommand : public ICommand
{
public:
	ExitCommand(std::vector<std::string> args);

	Result execute(Context& ctx);
	static unsigned int maxArg;
};

#endif