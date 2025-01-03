#ifndef OPTIONS_COMMAND_H
#define OPTIONS_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"


#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "options"


class OptionsCommand : public ICommand
{
public:
	OptionsCommand(std::vector<std::string> args);

	Result execute(Context& ctx);
	static unsigned int maxArg;

};

#endif