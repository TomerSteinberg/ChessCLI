#include "HistoryCommand.h"

HistoryCommand::HistoryCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int HistoryCommand::maxArg = 0;

Result HistoryCommand::execute(Context& ctx)
{
	std::string resultString = "";
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	std::vector<std::string> history = ctx.getCurrGame()->getHistory();
	for (size_t	i = 0; i < history.size(); i++)
	{
		resultString += std::to_string(i + 1) + ".\t";
		resultString += history[i] + "\t";
		if (i % 2 != 0)
		{
			resultString += "\n";
		}
	}
	return Result(false, true, resultString);
}
