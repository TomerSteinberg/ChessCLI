#include "Invoker.h"

void Invoker::invoke(Context& ctx, std::unique_ptr<ICommand>& cmd)
{
	if (cmd)
	{
		try 
		{
			cmd->execute(ctx);
		}
		catch (std::exception& error)
		{
			std::cout << error.what() << std::endl;
		}
	}
}
