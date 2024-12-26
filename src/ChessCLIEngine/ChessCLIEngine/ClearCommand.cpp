#include "ClearCommand.h"


ClearCommand::ClearCommand(std::vector<std::string> args) :ICommand(args)
{
}


unsigned int ClearCommand::maxArg = 0;


/*
* Clear command execute which clears the console
* input: Application state context
* output: none
*/
Result ClearCommand::execute(Context& ctx)
{
	system(CLEAR_CONSOLE);
	return Result(false);
}
