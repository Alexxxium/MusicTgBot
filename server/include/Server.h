#pragma once
#define WIN32_LEAN_AND_MEAN


#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "ServerQueues.h"



namespace srv
{
	static const int DEFAULT_LEN = 1024;
	static const std::string DEFAULT_PORT = "666";

	class Server {
	private:
		int  rescode;
		char recvbuff[DEFAULT_LEN];
		
		WSADATA  wsadata;
		ADDRINFO hints, *resinfo;
		SOCKET   client_socket, listen_socket;

		ServerQueues *queues;

	public:
		~Server();
		Server(Server&&) = delete;
		Server(const Server&) = delete;
		Server& operator=(Server&&) = delete;
		Server& operator=(const Server&) = delete;

		explicit Server(const std::string &port = DEFAULT_PORT);

		void listening();
		void close();

		std::string entryToQueue(std::string &&srvcmd) noexcept;
	};
}