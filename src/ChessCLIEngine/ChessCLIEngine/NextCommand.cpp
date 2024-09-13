#include "NextCommand.h"

NextCommand::NextCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int NextCommand::maxArg = 0;

Result NextCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	ctx.getCurrGame()->next();
	return Result(false);
}
