#include "EvaluateCommand.h"

EvaluateCommand::EvaluateCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int EvaluateCommand::maxArg = 0;

void EvaluateCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	std::cout << ctx.getCurrGame()->evaluate() << std::endl;
}
