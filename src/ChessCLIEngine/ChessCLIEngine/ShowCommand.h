#include <vector>
#include "ICommand.h"

#include "InvalidArgumentException.h"
#include "InvalidCommandException.h"

#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "show"


class ShowCommand : public ICommand
{
public:
	ShowCommand(std::vector<std::string> args);
	void execute(Context& ctx);

	static unsigned int maxArg;
};
