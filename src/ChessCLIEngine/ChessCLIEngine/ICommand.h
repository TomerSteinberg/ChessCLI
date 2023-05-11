#include "Context.h"
#include <vector>
#include <string>

#pragma once

class ICommand
{
public:
	ICommand(std::vector<std::string> args);

	virtual void execute(Context& ctx)=0;
protected:
	std::vector<std::string> _args;

};

