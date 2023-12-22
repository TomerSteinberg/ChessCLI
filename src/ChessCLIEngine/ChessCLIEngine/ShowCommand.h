#include <vector>
#include "ICommand.h"

#include "InvalidArgumentException.h"
#include "InvalidCommandException.h"

class ShowCommand : public ICommand
{
public:
	ShowCommand(std::vector<std::string> args);
	void execute(Context& ctx);

	static unsigned int maxArg;
};
