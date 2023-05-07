#include "Invoker.h"

void Invoker::invoke(Context& ctx, Command* cmd)
{
	cmd->execute(ctx);
	delete cmd;
}
