#pragma once
#include <vector>
#include <string>
#include "ICommand.h"

// run correct command based on operating system
#ifdef _WIN32
#define CLEAR_CONSOLE "cls"
#else
#define CLEAR_CONSOLE "clear"
#endif


class ClearCommand : public ICommand
{
public:
	ClearCommand(std::vector<std::string> args);
	void execute(Context& ctx);

	static int maxArg;
};

