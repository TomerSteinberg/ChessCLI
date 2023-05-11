#pragma once
#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"


class QuitCommand : public ICommand
{
public:
	QuitCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static int maxArg;

};

