#include "BotController.h"
#include "constants.h"



int main()
{
	auto *bot = mb::BotController::getInstanse(mb::init::TOKEN);
	bot->initCommands(mb::init::CMDLET);
	bot->listen();
}