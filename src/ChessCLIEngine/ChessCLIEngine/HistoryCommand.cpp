#include "HistoryCommand.h"

HistoryCommand::HistoryCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int HistoryCommand::maxArg = 0;

void HistoryCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	std::vector<std::string> history = ctx.getCurrGame()->getHistory();
	for (size_t	i = 0; i < history.size(); i++)
	{
		std::cout << std::to_string(i + 1) + ".\t";
		std::cout << history[i] + "\t";
		if (i % 2 != 0)
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
