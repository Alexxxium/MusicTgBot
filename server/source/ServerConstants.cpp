#include "ServerConstants.h"
#include <iostream>



namespace srv
{
	const std::string init::TOKEN = "6282754512:AAFaF5Gfi3uTTgNRndN8y3c3xac2y7b-25U";

	const std::unordered_set<std::string> init::SUPEXT
	{
		".mp3", ".wav", ".flac"
	};

	const std::unordered_map<std::string, int> init::QUEUES_COUNT
	{
		{ "download"    , 3 },
		{ "upload"      , 2 },
		{ "upload_group", 2 }
	};

	const std::unordered_map<std::string, Operation*> init::HANDLERS
	{
		{ "upload"      , new SendAudio      },
		{ "upload_group", new SendAudioGroup }
	};


	const std::exception
		err::INVALID_INDEX("Invalid index!"),
		err::INVALID_QUEUE_SIZE("Invalid queue size!"),
		err::INVALID_NOTATION("Invalid command notation!"),
		err::UNKOWN_CMD("Unknown command!"),
		err::NOT_EXISTED_PLAYLIST("Not existed playlist!");

	const std::string
		pth::USER_DATA_DIR = "D:/Prog/C++ prog/MusicTgBot/test data/";
}