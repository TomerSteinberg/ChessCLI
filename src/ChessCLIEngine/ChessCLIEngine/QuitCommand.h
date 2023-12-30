#ifndef QUIT_COMMAND_H
#define QUIT_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"



class QuitCommand : public ICommand
{
public:
	QuitCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;

};

#endif