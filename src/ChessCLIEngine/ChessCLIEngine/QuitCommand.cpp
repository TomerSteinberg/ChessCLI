#include "QuitCommand.h"

QuitCommand::QuitCommand(std::vector<std::string> args) : ICommand(args)
{
}

void QuitCommand::execute(Context& ctx)
{
	_exit(0);
}
