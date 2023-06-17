#include <iostream>
#include <string>
#include <memory>
#include "ICommand.h"
#include "Parser.h"
#include "Context.h"
#include "Invoker.h"

#define VERSION "v0.0.1"

#define DEBUG true
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
#include <iostream>
	
	// for debugging and testing bitboard

	int main(int argc, char** argv)
	{
		u64  attack = 0ULL;
		//attack = BitBoard::calcQueenAtkPattern(a1);
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			for (int j = 0; j < BOARD_HEIGHT; j++)
			{
				std::cout << GET_BIT(attack, (i * 8) + j) << " ";
			}
			std::cout << "\n";
		}
		std::cout << attack;
		return 0;
	}

#endif