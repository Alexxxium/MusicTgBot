#include "BotController.h"
#include "userdata.h"
#include "constants.h"
#include "Client.h"


int main() 
{
	constexpr auto serverpath = "\"D:/Prog/C++ prog/MusicTgBot/out/build/x64-Debug/server/Server.exe\"";

	mb::core::changeData();

	//std::thread server(system, serverpath);
	//server.detach();

	auto *bot = mb::BotController::getInstanse(mb::init::TOKEN);
	bot->initCommands(mb::init::CMDLET);
	bot->listen();
}