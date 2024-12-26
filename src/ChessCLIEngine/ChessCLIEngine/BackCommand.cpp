#include "BackCommand.h"

BackCommand::BackCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int BackCommand::maxArg = 0;

Result BackCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	ctx.getCurrGame()->back();
	return Result(false);
}
