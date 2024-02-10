#include "FenCommand.h"

FenCommand::FenCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int FenCommand::maxArg = 1;

void FenCommand::execute(Context& ctx)
{
	if(!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	if (this->m_args.size() > 0 )
	{
		if (this->m_args[0] == "-a" || this->m_args[0] == "--all-positions")
		{
			std::vector<std::string> fenStrings = ctx.getCurrGame()->getAllFen();
			for (int i = 0; i < fenStrings.size(); i++)
			{
				std::cout << fenStrings[i] << std::endl;
			}
			return;
		}
		throw InvalidArgumentException();
	}
	std::cout << ctx.getCurrGame()->getFen() << std::endl;
}
