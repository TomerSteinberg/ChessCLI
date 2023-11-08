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
#include <exception>


// for debugging and testing bitboard
int main(int argc, char** argv)
{
	BitBoard test("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	try // REMEMBER: edge case -> when rook or king taken remove ability to castle (use a specifc mask)
	{
		test.move(e2, e4)->printBoard();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	return 0;
}

#endif