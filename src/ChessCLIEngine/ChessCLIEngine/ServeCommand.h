#ifndef SERVE_COMMAND_H
#define SERVE_COMMAND_H
#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <vector>
#include <iostream>	
#include "ICommand.h"
#include "Context.h"
#include <thread>
#include "Parser.h"
#include "Invoker.h"
#include "InvalidCommandException.h"

#pragma warning(disable:4996) 
#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#ifdef COMMAND_NAME
#undef COMMAND_NAME
#endif
#define COMMAND_NAME "serve"
#define DEFAULT_PORT 6355
#define DEFAULT_ADDRESS "127.0.0.1"
#define MAXIMUM_CLIENTS 5
#define BUFFER_SIZE 4096

using nlohmann::json;

class ServeCommand : public ICommand
{
public:
	ServeCommand(std::vector<std::string> args);

	Result execute(Context& ctx);
	static unsigned int maxArg;
	static void initServer();
private:
	SOCKET createServerSocket() const;
	void bindServerSocket(const SOCKET serverSocket) const;
	void startListen(SOCKET serverSocket) const;
	static void serveClient(SOCKET clientSocket);
};

#endif