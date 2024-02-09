#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"



class ExitCommand : public ICommand
{
public:
	ExitCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;
};

#endif