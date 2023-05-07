#include <iostream>
#include <string>
#include <memory>
#include "Command.h"
#include "Parser.h"
#include "Context.h"
#include "Invoker.h"

#define VERSION "v0.0.1"

int main()
{
	std::string cmd;
	Context ctx;

	std::cout << "Duck Engine " << VERSION << std::endl;
	std::cout << "Type \"help\" for command information." << std::endl;

	while (true)
	{
		std::cout << "DuckEngine> ";
		std::getline(std::cin, cmd);

		Command* command = Parser::parseCommand(cmd);
		Invoker::invoke(ctx, command);
	}

	return 0;
}