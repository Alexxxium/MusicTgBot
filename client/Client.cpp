#include "Client.h"
#include "constants.h"



namespace mb
{
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