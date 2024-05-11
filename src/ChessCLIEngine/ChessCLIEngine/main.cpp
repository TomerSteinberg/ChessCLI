#include <iostream>
#include <string>
#include <memory>
#include "ICommand.h"
#include "Parser.h"
#include "Context.h"
#include "Invoker.h"

#define VERSION "v0.0.1"

#define debug false
#if !debug


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

		std::vector<std::unique_ptr<ICommand>> commands = Parser::parseCommand(cmd);
		Invoker::invoke(ctx, commands);
	}

	return 0;
}

#else
#include "BitBoard.h"

int main(int argc, char** argv)
{
	BitBoard b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	
	b.printBoard();
	b.makeMoveNoCopy({ 4503599627370496, 68719476736, NO_PROMOTION, false, false });
	b.makeMoveNoCopy({ 4096, 268435456, NO_PROMOTION, false, false });
	b.printBoard();
	return 0;
}
#endif