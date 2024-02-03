#include "OptionsCommand.h"

OptionsCommand::OptionsCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int OptionsCommand::maxArg = 0;

void OptionsCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException("options");
	}
	std::vector<std::string> continuations = ctx.getCurrGame()->getOptions();
	for (auto it = continuations.begin(); it != continuations.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}
