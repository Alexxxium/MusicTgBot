#pragma once
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>



namespace mb
{
	static const int DEFAULT_LEN = 128;
	static const std::string DEFAULT_PORT = "666";

	class Client {
	private:
		int  rescode;
		char recvbuff[DEFAULT_LEN];
		
		WSADATA  wsadata;
		SOCKET   connect_socket;
		ADDRINFO hints, *resinfo;

	public:
		~Client();
		Client(Client&&) = delete;
		Client(const Client&) = delete;
		Client& operator=(Client&&) = delete;
		Client& operator=(const Client&) = delete;


		explicit Client(const std::string &port = DEFAULT_PORT);

		// Redirect request to server and return answer
		std::string redirect(const std::string &srvcmd);
	};
}