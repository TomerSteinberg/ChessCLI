#include "ServeCommand.h"

ServeCommand::ServeCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int ServeCommand::maxArg = 3;

void ServeCommand::execute(Context& ctx)
{
	SOCKET serverSocket = createServerSocket();
	bindServerSocket(serverSocket); 
	startListen(serverSocket);
	std::cout << "Started Listening on port " << DEFAULT_PORT
		<< " With Address " << DEFAULT_ADDRESS << std::endl;
	bool running = true;
	while (running)
	{
		SOCKET clientSocket = accept(serverSocket, NULL, NULL);
		if (clientSocket != INVALID_SOCKET)
		{
			std::thread handleThread(serveClient, clientSocket);
			handleThread.detach();
		}
	}
	WSACleanup();
}


void ServeCommand::initServer()
{
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		throw std::exception("Command Error: Server Initialization Failed.\n");
	}
}

SOCKET ServeCommand::createServerSocket() const
{
	SOCKET serverSocket;
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		WSACleanup();
		throw std::exception("Command Error: Failed When Creating Server Socket.\n");
	}
	std::cout << "Socket was Created\n";
	return serverSocket;
}


void ServeCommand::bindServerSocket(const SOCKET serverSocket) const
{
	sockaddr_in service;
	service.sin_family = AF_INET;
	
	service.sin_addr.s_addr = inet_addr(DEFAULT_ADDRESS);
	service.sin_port = htons(DEFAULT_PORT);
	if (bind(serverSocket, reinterpret_cast<SOCKADDR*>(&service), sizeof(service)) == SOCKET_ERROR) {
		throw std::exception("Command Error: Failed to Bind Server Socket.\n");
		closesocket(serverSocket);
		WSACleanup();
	}
	std::cout << "Socket was bound\n";
}

void ServeCommand::startListen(SOCKET serverSocket) const
{
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception("Command Error: Failed to begin listening.\n");
		closesocket(serverSocket);
		WSACleanup();
	}
}

void ServeCommand::serveClient(SOCKET clientSocket)
{
	Context clientContext;
}
