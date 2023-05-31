#include <iostream>
#include <string>
#include <memory>
#include "ICommand.h"
#include "Parser.h"
#include "Context.h"
#include "Invoker.h"

#define VERSION "v0.0.1"

#define DEBUG false
#if !DEBUG

int main(int argc, char** argv)
{
	std::string cmd;
	Context ctx;

	std::cout << "Duck Engine " << VERSION << std::endl;
	std::cout << "Type \"help\" for command information." << std::endl;

	while (true)
	{
		std::cout << "DuckEngine> ";
		std::getline(std::cin, cmd);

		std::unique_ptr<ICommand> command = Parser::parseCommand(cmd);
		Invoker::invoke(ctx, command);
	}

	return 0;
}

#else
#include "BitBoard.h"
	int main(int argc, char** argv)
	{
		u64 bitBoards[SIDES][NUMBER_OF_PIECES] = { 1ULL, 2ULL, 4ULL, 8ULL, 16ULL, 32ULL, 64ULL,
		128ULL, 256ULL, 512ULL, 1024ULL, 1112048ULL};
		BitBoard board(bitBoards);

		std::cout << "  a b c d e f g h" << std::endl;
		return 0;
	}

#endif