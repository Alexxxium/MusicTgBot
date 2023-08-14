#include "BotController.h"
#include "constants.h"



int main()
{
	auto *bot = ctrl::BotController::getInstanse(init::TOKEN);
	bot->initCommands(init::CMD_BASE);
	bot->listen();
}