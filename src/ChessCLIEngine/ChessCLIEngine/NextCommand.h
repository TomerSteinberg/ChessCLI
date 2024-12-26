#ifndef NEXT_COMMAND_H
#define NEXT_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"

#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "next"


class NextCommand : public ICommand
{
public:
	NextCommand(std::vector<std::string> args);

	Result execute(Context& ctx);
	static unsigned int maxArg;

};

#endif