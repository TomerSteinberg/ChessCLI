#include "EvaluateCommand.h"

EvaluateCommand::EvaluateCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int EvaluateCommand::maxArg = 0;

Result EvaluateCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	return Result(false, true, std::to_string(ctx.getCurrGame()->evaluate()));
}
