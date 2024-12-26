#ifndef CLEAR_COMMAND_H
#define CLEAR_COMMAND_H

#include <vector>
#include <string>
#include "ICommand.h"


// run correct command based on operating system
#ifdef _WIN32
#define CLEAR_CONSOLE "cls"
#else
#define CLEAR_CONSOLE "clear"
#endif


class ClearCommand : public ICommand
{
public:
	ClearCommand(std::vector<std::string> args);
	Result execute(Context& ctx);

	static unsigned int maxArg;
};

#endif