#include <iostream>
#include <string>
#include <memory>
#include "ICommand.h"
#include "Parser.h"
#include "Context.h"
#include "Invoker.h"

#define VERSION "v0.0.1"
#define EMPTY_COMMAND ""

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

		if (cmd == EMPTY_COMMAND) { continue; }
		ICommand* command = Parser::parseCommand(cmd);
		if (!command) { continue; }
		Invoker::invoke(ctx, command);
	}

	return 0;
}