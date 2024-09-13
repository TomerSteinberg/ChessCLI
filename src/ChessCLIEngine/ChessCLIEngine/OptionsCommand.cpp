#include "OptionsCommand.h"

OptionsCommand::OptionsCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int OptionsCommand::maxArg = 0;

Result OptionsCommand::execute(Context& ctx)
{
	std::string resultString = "";
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	std::vector<std::string> continuations = ctx.getCurrGame()->getOptions();
	for (auto it = continuations.begin(); it != continuations.end(); it++)
	{
		resultString += *it + "\n";
	}
	return Result(false, true, resultString);
}
