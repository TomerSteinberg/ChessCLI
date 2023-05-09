#include "Invoker.h"

void Invoker::invoke(Context& ctx, ICommand* cmd)
{
	cmd->execute(ctx);
	delete cmd;
}
