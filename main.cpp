#include "BotController.h"
#include "constants.h"



int main()
{
	auto *bot = mb::BotController::getInstanse(mb::init::TOKEN);
	bot->initCommands(mb::init::CMD_BASE);
	bot->listen();
}