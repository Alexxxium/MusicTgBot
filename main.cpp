#include "BotController.h"
#include "constants.h"


int main()
{
	auto *bot = ctrl::BotController::getInstanse("6282754512:AAFaF5Gfi3uTTgNRndN8y3c3xac2y7b-25U");
	bot->initCommands(init::CMD_BASE);
	bot->listen();
}