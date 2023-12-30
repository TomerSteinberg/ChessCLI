#include "Invoker.h"

void Invoker::invoke(Context& ctx, std::vector<std::unique_ptr<ICommand>>& cmds)
{
	if (cmds.size())
	{
		try 
		{
			for (auto cmd = cmds.begin(); cmd != cmds.end(); cmd++)
			{
				cmd->get()->execute(ctx);
			}
		}
		catch (std::exception& error)
		{
			std::cout << error.what() << std::endl;
		}
	}
}
