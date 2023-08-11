#include "BotController.h"
#include "constants.h"



int main()
{
	auto *bot = ctrl::BotController::getInstanse(TOKEN);
	bot->initCommands(init::CMD_BASE);
	bot->listen();
}