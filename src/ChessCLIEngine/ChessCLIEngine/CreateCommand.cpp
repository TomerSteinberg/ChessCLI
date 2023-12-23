#include "CreateCommand.h"

CreateCommand::CreateCommand(std::vector<std::string> args) :ICommand(args)
{
}

unsigned int CreateCommand::maxArg = 6;

void CreateCommand::execute(Context& ctx)
{
	if (this->m_args.size() > 0)
	{
		if (!std::regex_match(this->combineArgs(), std::regex(FEN_REGEX)))
		{
			throw InvalidArgumentException("Invalid FEN string");
		}

	}

	if (ctx.getCurrGame())
	{
		ctx.deleteGame();
	}

	if (this->m_args.size() != 0)
	{
		ctx.newGame(this->combineArgs());
		return;
	}
	ctx.newGame(DEFAULT_STARTING_FEN);
}

std::string CreateCommand::combineArgs() const
{
	std::string fen = "";
	int argNum = 0;
	for (argNum = 0; argNum < this->m_args.size(); argNum++)
	{
		fen += this->m_args[argNum] + " ";
	}

	if (argNum < 3)
	{
		throw InvalidArgumentException("Missing Arguments");
	}
	return fen;
}
