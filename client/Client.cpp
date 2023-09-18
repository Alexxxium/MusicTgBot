#include "Client.h"
#include "constants.h"



namespace mb
{
	Client_t::Client_t() {
		int rescode;
		std::string buffer;
		char recvbuff[512];

		WSADATA wsadata;
		ADDRINFO hints;
		ADDRINFO *addr_res = nullptr;
		SOCKET connect_socket = INVALID_SOCKET;

		rescode = WSAStartup(MAKEWORD(2, 2), &wsadata);
		if (rescode != 0) {
			std::cout << "WWAStartup failed! Error-code:\t" << rescode << std::endl;
			throw 1;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		rescode = getaddrinfo("localhost", "666", &hints, &addr_res);
		if (rescode != 0) {
			std::cout << "getaddrinfo failed! Error-code:\t" << rescode << std::endl;
			WSACleanup();
			throw 1;
		}

		connect_socket = socket(addr_res->ai_family, addr_res->ai_socktype, addr_res->ai_protocol);
		if (connect_socket == INVALID_SOCKET) {
			std::cout << "Socket initialization failed!" << std::endl;
			freeaddrinfo(addr_res);
			WSACleanup();
			throw 1;
		}

		rescode = connect(connect_socket, addr_res->ai_addr, addr_res->ai_addrlen);
		if (rescode == SOCKET_ERROR) {
			std::cout << "Connection failed!" << std::endl;
			closesocket(connect_socket);
			connect_socket = INVALID_SOCKET;
			freeaddrinfo(addr_res);
			WSACleanup();
			throw 1;
		}


		/// AFTER CONNECTION
		
		buffer = "Test message for server!";
		rescode = send(connect_socket, buffer.c_str(), buffer.size(), 0);
		if (rescode == SOCKET_ERROR) {
			std::cout << "Sent was failed! Error-code:\t" << rescode << std::endl;
			closesocket(connect_socket);
			freeaddrinfo(addr_res);
			WSACleanup();
			throw 1;
		}

		std::cout << "Sent:\t" << rescode << " byites" << std::endl;

		rescode = shutdown(connect_socket, SD_SEND);
		if (rescode == SOCKET_ERROR) {
			std::cout << "Shutdown failed!" << std::endl;
			closesocket(connect_socket);
			freeaddrinfo(addr_res);
			WSACleanup();
			throw 1;
		}


		do {
			ZeroMemory(recvbuff, sizeof(recvbuff));                      // !!! (use 512 len)
			rescode = recv(connect_socket, recvbuff, sizeof(recvbuff), 0);
			if (rescode > 0) {
				std::cout <<
					"Recived byits: \t" << rescode << "\n" <<
					"Recived buffer:\t" << recvbuff << std::endl;
			}
			else if (rescode == 0) {
				std::cout << "Connection was closed!" << std::endl;
			}
			else {
				std::cout << "recv failed! Error-code:\t" << rescode << std::endl;
			}
		} while (rescode > 0);

		closesocket(connect_socket);
		freeaddrinfo(addr_res);
		WSACleanup();
	}



	Client::~Client() {
		closesocket(connect_socket);
		freeaddrinfo(resinfo);
		WSACleanup();
	}

	Client::Client(const std::string &port) {
		constexpr auto host = "localhost";
		
		resinfo = nullptr;
		connect_socket = INVALID_SOCKET;

		rescode = WSAStartup(MAKEWORD(2, 2), &wsadata);
		if (rescode != 0) {
			throw err::INIT_CLIENT_FAILED;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family   = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		rescode = getaddrinfo(host, port.c_str(), &hints, &resinfo);
		if (rescode != 0) {
			WSACleanup();
			throw err::INIT_ADDRINFO_FAILED;
		}

		connect_socket = socket(resinfo->ai_family, resinfo->ai_socktype, resinfo->ai_protocol);
		if (connect_socket == INVALID_SOCKET) {
			freeaddrinfo(resinfo);
			WSACleanup();
			throw err::INIT_SOCKET_FAILED;
		}

		rescode = connect(connect_socket, resinfo->ai_addr, resinfo->ai_addrlen);
		if (rescode == SOCKET_ERROR) {
			closesocket(connect_socket);
			freeaddrinfo(resinfo);
			WSACleanup();
			throw err::INIT_CONNECTION_FAILED;
		}

		ZeroMemory(recvbuff, sizeof(recvbuff));
	}

	std::string Client::redirect(const std::string &srvcmd) {
		constexpr int flag = 0;

		rescode = send(connect_socket, srvcmd.c_str(), srvcmd.size(), flag);
		if (rescode == SOCKET_ERROR) {
			throw err::SENDING_FAILED;
		}

		ZeroMemory(recvbuff, sizeof(recvbuff));
		rescode = recv(connect_socket, recvbuff, sizeof(recvbuff), flag);

		if (rescode > 0) {
			return recvbuff;
		}
		else if (rescode == 0) {
			throw err::CLOSED_CONNECTION;
		}
		else {
			throw err::RECEVING_FAILED;
		}
	}
}