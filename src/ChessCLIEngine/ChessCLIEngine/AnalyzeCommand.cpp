#include "AnalyzeCommand.h"

AnalyzeCommand::AnalyzeCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int AnalyzeCommand::maxArg = 0;


void AnalyzeCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	ctx.getCurrGame()->analyze();
}
