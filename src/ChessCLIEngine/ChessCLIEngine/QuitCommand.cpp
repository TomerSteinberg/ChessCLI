#include "QuitCommand.h"

QuitCommand::QuitCommand(std::vector<std::string> args) : ICommand(args)
{
}


int QuitCommand::maxArg = 0;


/*
* Quit command execute function for exiting the application
* input: Application state context
* output: none
*/
void QuitCommand::execute(Context& ctx)
{
	_exit(0);
}
