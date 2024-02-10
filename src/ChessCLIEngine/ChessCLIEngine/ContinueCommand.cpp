#include "ContinueCommand.h"

ContinueCommand::ContinueCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int ContinueCommand::maxArg = 0;

void ContinueCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	ctx.getCurrGame()->playBest();
}
