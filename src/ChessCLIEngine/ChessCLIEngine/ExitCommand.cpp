#include "ExitCommand.h"

ExitCommand::ExitCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int ExitCommand::maxArg = 1;

void ExitCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	ctx.deleteGame();
}
