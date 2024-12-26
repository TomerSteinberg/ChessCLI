#include "TruncateCommand.h"

TruncateCommand::TruncateCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int TruncateCommand::maxArg = 0;

Result TruncateCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException("truncate");
	}
	ctx.getCurrGame()->truncate();
	return Result(false);
}
