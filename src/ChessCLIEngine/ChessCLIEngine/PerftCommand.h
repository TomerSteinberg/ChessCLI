#ifndef PERFT_COMMAND_H
#define PERFT_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidArgumentException.h"
#include "InvalidCommandException.h"
#include <chrono>
#include <regex>


#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "perft"

#define INTEGER_REGEX "[0-9]+$"

#define INVALID_PERFT_ARGUMENTS InvalidArgumentException("Usage -> perft <depth> [-r]")

class PerftCommand : public ICommand
{
public:
	PerftCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;
};

#endif