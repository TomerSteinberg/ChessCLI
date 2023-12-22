#include "ICommand.h"
#include <regex>



#define FEN_REGEX "/^(?:(?:[PNBRQK]+|[1-8])\/){7}(?:[PNBRQK]+|[1-8])$"
#define DEFAULT_STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#pragma once
class CreateCommand : public ICommand
{
public:
	CreateCommand(std::vector<std::string> args);
	void execute(Context& ctx);

	static unsigned int maxArg;
};

