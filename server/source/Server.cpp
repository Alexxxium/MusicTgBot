#include "Server.h"
#include "ServerConstants.h"
#include <iostream>
#include <fstream>



namespace srv 
{
	Server::~Server() {
		close();
	}

	Server::Server(const std::string &port) {
		resinfo = nullptr;
		client_socket = INVALID_SOCKET;
		listen_socket - INVALID_SOCKET;

		rescode = WSAStartup(MAKEWORD(2, 2), &wsadata);
		if (rescode != 0) {
			throw err::INIT_SERVER_FAILED;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family   = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags    = AI_PASSIVE;

		rescode = getaddrinfo(NULL, port.c_str(), &hints, &resinfo);
		if (rescode != 0) {
			WSACleanup();
			throw err::INIT_ADDRINFO_FAILED;
		}

		listen_socket = socket(resinfo->ai_family, resinfo->ai_socktype, resinfo->ai_protocol);
		if (listen_socket == INVALID_SOCKET) {
			freeaddrinfo(resinfo);
			WSACleanup();
			throw err::INIT_SOCKET_FAILED;
		}

		rescode = bind(listen_socket, resinfo->ai_addr, resinfo->ai_addrlen);
		if (rescode == SOCKET_ERROR) {
			closesocket(listen_socket);
			freeaddrinfo(resinfo);
			WSACleanup();
			throw err::BINDING_FAILED;
		}

		rescode = listen(listen_socket, 1);
		if (rescode == SOCKET_ERROR) {
			closesocket(listen_socket);
			freeaddrinfo(resinfo);
			WSACleanup();
			throw err::LISTENING_FAILED;
		}

		ZeroMemory(recvbuff, sizeof(recvbuff));
		queues = ServerQueues::getInstanse(init::QUEUES_COUNT);
	}

	void Server::listening() {
		constexpr auto log = "The connection was closed by the client!";

		client_socket = accept(listen_socket, nullptr, nullptr);
		if (client_socket == INVALID_SOCKET) {
			throw err::ACCEPTING_FAILED;
		}

		do {
			ZeroMemory(recvbuff, sizeof(recvbuff)); 
			rescode = recv(client_socket, recvbuff, sizeof(recvbuff), 0);
			if (rescode > 0) {
				std::cout << "Recv. data:\t" << recvbuff << std::endl;
				std::string response = entryToQueue(recvbuff);
				rescode = send(client_socket, response.c_str(), response.size(), 0);
				if (rescode == SOCKET_ERROR) {
					throw err::RESPONSE_FAILED;
				}
			}
			else if (rescode == 0) {
				std::cout << log << std::endl;
			}
			else {
				throw err::RECEVING_FAILED;
			}
		} while (rescode > 0);
	}

	void Server::close() {
		closesocket(client_socket);
		closesocket(listen_socket);
		freeaddrinfo(resinfo);
		WSACleanup();
	}

	std::string Server::entryToQueue(const std::string &srvcmd) noexcept {
		constexpr auto
			unknown_err = u8"Неизвестная ошибка!",
			good_bit    = u8"запрос принят и отправлен в очередь!",
			ib_         = u8"<i><b>Ответ от сервера: </b>",
			_i          = u8"</i>";
			

		try {
			queues->accept(srvcmd);
		}
		catch (const std::exception &exc) {
			return (std::string) ib_ + exc.what() + _i;
		}
		catch (...) {
			return (std::string) ib_ + unknown_err + _i;
		}

		return (std::string)ib_ + good_bit + _i;
	}
}