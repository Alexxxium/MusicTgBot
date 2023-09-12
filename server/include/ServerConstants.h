#pragma once
#include "ServerOperations.h"
#include <unordered_map>
#include <functional>
#include <exception>
#include <string>


namespace srv 
{
	class init {
	public:
		static std::unordered_map<std::string, int> QUEUES_COUNT;
		static std::unordered_map<std::string, Operation*> HANDLERS;
	};

	class err {
	public:
		static std::exception
			INVALID_QUEUE_SIZE,
			INVALID_INDEX,
			UNKOWN_CMD;
	};
}