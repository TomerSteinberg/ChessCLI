#ifndef HISTORY_COMMAND_H
#define HISTORY_COMMAND_H_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"



class HistoryCommand : public ICommand
{
public:
	HistoryCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;

};

#endif