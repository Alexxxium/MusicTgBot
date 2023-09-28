#pragma once
#include "ServerOperations.h"
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <exception>
#include <string>


namespace srv 
{
	class init {
	public:
		static const std::string TOKEN;
		static const std::unordered_set<std::string> SUPEXT;
		static const std::unordered_map<std::string, int> QUEUES_COUNT;
		static const std::unordered_map<std::string, Operation*> HANDLERS;
	};

	class err {
	public:
		static const std::exception
			INVALID_QUEUE_SIZE,
			INVALID_NOTATION,
			INVALID_INDEX,
			UNKOWN_CMD,
			NOT_EXISTED_PLAYLIST,
			INVALID_PATH,
			
			INIT_SERVER_FAILED,
			INIT_ADDRINFO_FAILED,
			INIT_SOCKET_FAILED,
			INIT_CONNECTION_FAILED,
			BINDING_FAILED,
			LISTENING_FAILED,
			ACCEPTING_FAILED,
			RECEVING_FAILED,
			RESPONSE_FAILED;
	};

	class pth {
	public:
		static const std::string
			USER_DATA_DIR,
			BUFFER_DIR,
			DOWNLOAD_SCRIPT;
	};
}