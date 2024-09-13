#include "FenCommand.h"

FenCommand::FenCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int FenCommand::maxArg = 1;

Result FenCommand::execute(Context& ctx)
{
	std::string resultString = "";
	if(!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	if (this->m_args.size() > 0 )
	{
		if (this->m_args[0] == "-a" || this->m_args[0] == "--all-positions")
		{
			std::vector<std::string> fenStrings = ctx.getCurrGame()->getAllFen();
			for (size_t i = 0; i < fenStrings.size(); i++)
			{
				resultString += fenStrings[i] + "\n";
			}
			return Result(false, true, resultString);
		}
		throw InvalidArgumentException();
	}
	return Result(false, true, ctx.getCurrGame()->getFen());
}
