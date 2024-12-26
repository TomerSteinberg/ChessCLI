#ifndef POSITION_COMMAND_H
#define POSITION_COMMAND_H

#include <vector>
#include <string>
#include "InvalidArgumentException.h"
#include "InvalidCommandException.h"
#include "ICommand.h"
#include <regex>

#define INTEGER_REGEX "[0-9]+$"

#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "position"


class PositionCommand : public ICommand
{
public:
	PositionCommand(std::vector<std::string> args);
	Result execute(Context& ctx);

	static unsigned int maxArg;
};

#endif