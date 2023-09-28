#include "BotController.h"
#include "userdata.h"
#include "constants.h"
#include "Client.h"


int main() 
{
	mb::core::changeData();
	std::thread server(system, "\"D:/Prog/C++ prog/MusicTgBot/out/build/x64-Debug/server/Server.exe\"");

	auto *bot = mb::BotController::getInstanse(mb::init::TOKEN);
	bot->initCommands(mb::init::CMDLET);
	bot->listen();
}