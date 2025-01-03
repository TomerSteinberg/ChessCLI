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

#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "dump"


class DumpCommand : public ICommand
{
public:
	DumpCommand(std::vector<std::string> args);

	Result execute(Context& ctx);
	static unsigned int maxArg;
private:
	bool matchRegexVector();
};

#endif