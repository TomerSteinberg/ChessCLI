#ifndef ANALYZE_COMMAND_H
#define ANALYZE_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"

#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "analyze"

class AnalyzeCommand : public ICommand
{
public:
	AnalyzeCommand(std::vector<std::string> args);

	Result execute(Context& ctx);
	static unsigned int maxArg;

};

#endif