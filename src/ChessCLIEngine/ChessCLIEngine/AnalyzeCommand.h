#ifndef ANALYZE_COMMAND_H
#define ANALYZE_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"

#define COMMAND_NAME "analyze"

class AnalyzeCommand : public ICommand
{
public:
	AnalyzeCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;

};

#endif