#ifndef FEN_COMMAND_H
#define FEN_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"



class FenCommand : public ICommand
{
public:
	FenCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;

};

#endif