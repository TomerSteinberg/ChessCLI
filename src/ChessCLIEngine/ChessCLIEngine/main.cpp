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
	try 
	{
		test.move(g1,f3)->move(g8, f6)->move(g2,g3)->move(g7,g6)->move(f1,g2)->
			move(f8,g7)->castleMove(false)->move(h7,h5)->printBoard();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	return 0;
}

#endif