#ifndef OPTIONS_COMMAND_H
#define OPTIONS_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"



class OptionsCommand : public ICommand
{
public:
	OptionsCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;

};

#endif