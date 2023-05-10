#include "Invoker.h"

void Invoker::invoke(Context& ctx, ICommand* cmd)
{
	if (cmd)
	{
		cmd->execute(ctx);
		delete cmd;
	}
}
