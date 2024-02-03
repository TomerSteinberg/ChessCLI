#include "NextCommand.h"

NextCommand::NextCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int NextCommand::maxArg = 0;

void NextCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException("next");
	}
	ctx.getCurrGame()->next();
}
