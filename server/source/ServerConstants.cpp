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
		{ "upload_group", 2 },
		{ "url_upload"  , 2 }
	};

	const std::unordered_map<std::string, Operation*> init::HANDLERS
	{
		{ "upload"      , new SendAudio          },
		{ "upload_group", new SendAudioGroup     },
		{ "download"    , new DownloadAudioGroup },
		{ "url_upload"  , new SendAudioFromURL   }
	};


	const std::exception
		err::INVALID_INDEX("Invalid index!"),
		err::INVALID_QUEUE_SIZE("Invalid queue size!"),
		err::INVALID_NOTATION("Invalid command notation!"),
		err::UNKOWN_CMD("Unknown command!"),
		err::NOT_EXISTED_PLAYLIST("Not existed playlist!"),
		err::INVALID_PATH("Invalid path to user data!"),
		
		err::INIT_SERVER_FAILED("Can`t initializing server!"),
		err::INIT_ADDRINFO_FAILED("Can`t initializing ADDRINF struct!"),
		err::INIT_SOCKET_FAILED("Can`t initializing socket!"),
		err::INIT_CONNECTION_FAILED("Can`t initializing connection!"),
		err::BINDING_FAILED("Error binding socket!"),
		err::LISTENING_FAILED("Error listening socket!"),
		err::ACCEPTING_FAILED("Error accepting socket!"),
		err::RECEVING_FAILED("Error receiving message!"),
		err::RESPONSE_FAILED("Error sending response!");

	const std::string
		pth::USER_DATA_DIR = u8"D:/Prog/C++ prog/MusicTgBot/test data/",
		pth::BUFFER_DIR = u8"D:/Prog/C++ prog/MusicTgBot/buffer data/",
		pth::DOWNLOAD_SCRIPT = u8"D:/Prog/C++ prog/MusicTgBot/server/scripts/script.bat";
}