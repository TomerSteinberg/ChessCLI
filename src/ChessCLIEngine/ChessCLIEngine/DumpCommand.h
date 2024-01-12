#ifndef DUMP_COMMAND_H
#define DUMP_COMMAND_H

#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"
#include <bitset>
#include <Bits.h>
#include <regex>

#define FLAGS_REGEX "^((-b)|(-l)|(-h))$"

class DumpCommand : public ICommand
{
public:
	DumpCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;
private:
	bool matchRegexVector();
};

#endif