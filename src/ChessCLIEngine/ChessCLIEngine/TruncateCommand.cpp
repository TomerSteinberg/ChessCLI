#include "TruncateCommand.h"

TruncateCommand::TruncateCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int TruncateCommand::maxArg = 0;

void TruncateCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException("truncate");
	}
	ctx.getCurrGame()->truncate();
}
