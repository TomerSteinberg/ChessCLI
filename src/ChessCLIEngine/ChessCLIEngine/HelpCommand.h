#pragma once
#include <vector>
#include "ICommand.h"
#include "Context.h"


class HelpCommand : public ICommand
{
public:
	HelpCommand(std::vector<std::string> args);

	void execute(Context& ctx);
};
