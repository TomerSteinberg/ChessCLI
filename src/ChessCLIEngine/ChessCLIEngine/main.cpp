#include <iostream>
#include <string>
#include <memory>
#include "ICommand.h"
#include "Parser.h"
#include "Context.h"
#include "Invoker.h"

#define VERSION "v0.0.1"

#define TEST true
#if !TEST

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
#include <iostream>
#include <io.h>
#include <fcntl.h>


// for debugging and testing bitboard

int main(int argc, char** argv)
{
	BitBoard test("6b1/4PP2/1k1b3r/p3B3/P2N3P/1Kpp1R2/4q3/8 w - - 0 1");
	test.printBoard();
	return 0;
}

#endif