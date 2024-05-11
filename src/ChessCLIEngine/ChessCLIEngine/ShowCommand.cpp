#include "ShowCommand.h"

ShowCommand::ShowCommand(std::vector<std::string> args) : ICommand(args)
{
}


unsigned int ShowCommand::maxArg = 1;


void ShowCommand::execute(Context& ctx)
{
	if (this->m_args.size() > 0)
	{
		if (this->m_args[0] != "-u" && this->m_args[0] != "--unicode")
		{
			throw InvalidArgumentException();
		}
	}
	if (ctx.getCurrGame())
	{
		this->m_args.size() == 0 ? ctx.getCurrGame()->showPosition() :
			ctx.getCurrGame()->showPosition(true);
		return;
	}
	throw InvalidCommandException(COMMAND_NAME);
}
