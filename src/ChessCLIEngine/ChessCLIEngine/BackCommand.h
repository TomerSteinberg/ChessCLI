#ifndef BACK_COMMAND_H
#define BACK_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"

#define COMMAND_NAME "back"


class BackCommand : public ICommand
{
public:
	BackCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;

};

#endif