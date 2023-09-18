#include "BotController.h"
#include "constants.h"
#include "Client.h"


int main() 
{
	std::thread server(system, "\"D:/Prog/C++ prog/MusicTgBot/out/build/x64-Release/server/Server.exe\"");
	server.detach();

	auto *bot = mb::BotController::getInstanse(mb::init::TOKEN);
	bot->initCommands(mb::init::CMDLET);
	bot->listen();
}