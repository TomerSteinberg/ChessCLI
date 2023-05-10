#include "ClearCommand.h"


ClearCommand::ClearCommand(std::vector<std::string> args) :ICommand(args)
{
}


/*
* Clear command execute which clears the console
* input: Application state context
* output: none
*/
void ClearCommand::execute(Context& ctx)
{
	system(CLEAR_CONSOLE);
}
