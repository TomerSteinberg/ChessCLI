#ifndef POSITION_COMMAND_H
#define POSITION_COMMAND_H

#include <vector>
#include <string>
#include "InvalidArgumentException.h"
#include "InvalidCommandException.h"
#include "ICommand.h"
#include <regex>

#define INTEGER_REGEX "[0-9]+$"

class PositionCommand : public ICommand
{
public:
	PositionCommand(std::vector<std::string> args);
	void execute(Context& ctx);

	static unsigned int maxArg;
};

#endif