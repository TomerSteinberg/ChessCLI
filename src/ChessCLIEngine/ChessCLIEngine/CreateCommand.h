#include "ICommand.h"
#include <regex>
#include <iostream>

#include "InvalidArgumentException.h"


#define FEN_REGEX "([rnbqkpRNBQKP1-8]+\\/){7}([rnbqkpRNBQKP1-8]+)\\s[bw-]\\s(([a-hkqA-HKQ]{1,4})|(-))\\s(([a-h][12345678] ?)|(-)|(- ))(\\s\\d+\\s\\d+\\s*)?$"
#define DEFAULT_STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#pragma once
class CreateCommand : public ICommand
{
public:
	CreateCommand(std::vector<std::string> args);
	void execute(Context& ctx);

	static unsigned int maxArg;
private:
	std::string combineArgs() const;
};

