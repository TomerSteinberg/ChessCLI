#include "PositionCommand.h"

PositionCommand::PositionCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int PositionCommand::maxArg = 1;

void PositionCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException("position");
	}
	if (this->m_args.size() != 1)
	{
		throw InvalidArgumentException("Missing parameter. <Usage>: position [index of position]");
	}
	if (!std::regex_match(this->m_args[0], std::regex(INTEGER_REGEX)))
	{
		throw InvalidArgumentException("Invalid parameter. <Usage>: position [index of position]");
	}
	if(!ctx.getCurrGame()->toPosition(std::stoi(this->m_args[0])))
	{
		throw InvalidArgumentException("Specified position doesn't exist");
	}
}
