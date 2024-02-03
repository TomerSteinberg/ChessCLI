#ifndef EVALUATE_COMMAND_H
#define EVALUATE_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"



class EvaluateCommand : public ICommand
{
public:
	EvaluateCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;
};

#endif