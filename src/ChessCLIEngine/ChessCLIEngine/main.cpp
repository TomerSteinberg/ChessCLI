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
	BitBoard test("6k1/b7/8/8/5p2/7p/7P/7K b - - 0 54");
	try 
	{
		test.move(a7, b8)->move(h1,g1)->printBoard();
		//test.printBoard();
		//std::cout << test.isStale();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	return 0;
}

#endif