#include "Invoker.h"

void Invoker::invoke(Context& ctx, std::unique_ptr<ICommand>& cmd)
{
	if (cmd)
	{
		cmd->execute(ctx);
	}
}
