#ifndef HISTORY_COMMAND_H
#define HISTORY_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"

#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "history"


class HistoryCommand : public ICommand
{
public:
	HistoryCommand(std::vector<std::string> args);

	Result execute(Context& ctx);
	static unsigned int maxArg;

};

#endif