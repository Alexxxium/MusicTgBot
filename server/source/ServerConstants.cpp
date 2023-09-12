#include "ServerConstants.h"
#include <iostream>



namespace srv
{
	std::unordered_map<std::string, int> init::QUEUES_COUNT
	{
		{ "download",     3 },
		{ "upload",       2 },
		{ "upload_group", 2 }
	};

	std::unordered_map<std::string, Operation*> init::HANDLERS
	{
		{ "upload", new SendAudio }
	};


	std::exception
		err::INVALID_INDEX("Invalid index!"),
		err::INVALID_QUEUE_SIZE("Invalid queue size!"),
		err::UNKOWN_CMD("Unknown command!");
}