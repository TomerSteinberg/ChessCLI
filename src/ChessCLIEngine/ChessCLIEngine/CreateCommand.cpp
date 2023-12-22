#include "CreateCommand.h"

CreateCommand::CreateCommand(std::vector<std::string> args) :ICommand(args)
{
}

unsigned int CreateCommand::maxArg = 1;

void CreateCommand::execute(Context& ctx)
{
	if (this->m_args.size() == 1)
	{
		if (!std::regex_match(this->m_args[0], std::regex(FEN_REGEX)))
		{
			throw std::exception("Argument Error: Invalid FEN string");
		}

	}

	if (ctx.getCurrGame())
	{
		ctx.deleteGame();
	}

	if (this->m_args.size() != 0)
	{
		ctx.newGame(this->m_args[0]);
		return;
	}
	ctx.newGame(DEFAULT_STARTING_FEN);
}
