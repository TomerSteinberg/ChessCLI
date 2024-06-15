#pragma comment (lib, "ws2_32.lib")
#define WIN32_LEAN_AND_MEAN


#include <WinSock2.h>
#include <Windows.h>
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
	ServeCommand::initServer();
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
	WSACleanup();
	return 0;
}

#else
#endif