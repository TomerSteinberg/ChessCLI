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
//#include <websocketpp/config/asio_no_tls.hpp>
//#include <websocketpp/server.hpp>
#include <set>
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
//using websocketpp::connection_hdl;
//using server = websocketpp::server<websocketpp::config::asio>;


class ServeCommand : public ICommand
{
public:
	ServeCommand(std::vector<std::string> args);

	Result execute(Context& ctx);
	static unsigned int maxArg;
	static void initServer();


private:
	//server m_server;
	/*std::set<connection_hdl, std::owner_less<connection_hdl>> m_connections;
	std::mutex m_mutex;*/
	SOCKET createServerSocket() const;
	void bindServerSocket(const SOCKET serverSocket) const;
	void startListen(SOCKET serverSocket) const;
	static void serveClient(SOCKET clientSocket);

	//void on_message(connection_hdl hdl, server::message_ptr msg) {
	//	std::lock_guard<std::mutex> lock(m_mutex);
	//	std::cout << "Message received: " << msg->get_payload() << std::endl;

	//	// Echo the message back to the client
	//	m_server.send(hdl, msg->get_payload(), msg->get_opcode());
	//}

	//void on_open(connection_hdl hdl) {
	//	std::lock_guard<std::mutex> lock(m_mutex);
	//	m_connections.insert(hdl);
	//	std::cout << "Client connected" << std::endl;
	//}

	//void on_close(connection_hdl hdl) {
	//	std::lock_guard<std::mutex> lock(m_mutex);
	//	m_connections.erase(hdl);
	//	std::cout << "Client disconnected" << std::endl;
	//}

	//void run(std::uint16_t port) {
	//	m_server.listen(port);
	//	m_server.start_accept();

	//	// Launch server in a separate thread
	//	std::thread server_thread([&]() { m_server.run(); });
	//	server_thread.join();
	//}
};

#endif