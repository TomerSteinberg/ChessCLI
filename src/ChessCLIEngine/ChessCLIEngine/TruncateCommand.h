#ifndef TRUNCATE_COMMAND_H
#define TRUNCATE_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"



class TruncateCommand : public ICommand
{
public:
	TruncateCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;

};

#endif