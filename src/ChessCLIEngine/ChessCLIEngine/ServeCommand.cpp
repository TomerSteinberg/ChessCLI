#include "ServeCommand.h"



unsigned int ServeCommand::maxArg = 3;

ServeCommand::ServeCommand(std::vector<std::string> args) : ICommand(args)
{
	//m_server.init_asio();

	//// Set message handler
	//m_server.set_message_handler(std::bind(
	//	&ServeCommand::on_message, this, std::placeholders::_1, std::placeholders::_2));

	//// Set open handler
	//m_server.set_open_handler(std::bind(
	//	&ServeCommand::on_open, this, std::placeholders::_1));

	//// Set close handler
	//m_server.set_close_handler(std::bind(
	//	&ServeCommand::on_close, this, std::placeholders::_1));
}

Result ServeCommand::execute(Context& ctx)
{
	return Result(false);
	//this->run(DEFAULT_PORT);
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
	const std::string initalGet = "GET / HTTP/1.1";
	Context clientContext;
	try
	{

		while (true)
		{
			char buffer[BUFFER_SIZE] = { 0 };
			json respJson;

			recv(clientSocket, buffer, BUFFER_SIZE, 0);
			std::string command(buffer);
			if (command.find(initalGet) != std::string::npos)
			{
				const std::string resp = "HTTP/1.1 101 Switching Protocols\nConnection: Upgrade\nSec-WebSocket-Accept: EDJa7WCAQQzMCYNJM42Syuo9SqQ=\nUpgrade: websocket";
				send(clientSocket, resp.c_str(), resp.length(), 0);
				std::cout << resp << std::endl;
				continue;
			}
			std::vector<std::unique_ptr<ICommand>> commands = Parser::parseCommand(command);
			Result commandResult = Invoker::invoke(clientContext, commands, false);
			Result::toJson(respJson, commandResult);
			send(clientSocket, respJson.dump().c_str(), respJson.dump().length(), 0);
		}
	}
	catch (...) 
	{
		closesocket(clientSocket);
		std::cout << "Closed Connection with a Client Due to Unforeseen Error\n";
	}
}
