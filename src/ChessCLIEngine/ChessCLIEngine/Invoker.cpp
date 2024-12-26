#include "Invoker.h"

Result Invoker::invoke(Context& ctx, std::vector<std::unique_ptr<ICommand>>& cmds, const bool logResult)
{
	Result commandResult = Result(false, true, "No Data Was Sent");
	if (cmds.size())
	{
		try 
		{
			for (auto cmd = cmds.begin(); cmd != cmds.end(); cmd++)
			{
				commandResult = cmd->get()->execute(ctx);
			}
		}
		catch (std::exception& error)
		{
			commandResult = Result(true, true ,std::string(error.what())) ;
		}
		if (logResult && commandResult.isMessage)
		{
			std::cout << commandResult.message << std::endl;
		}
	}
	return commandResult;
}
