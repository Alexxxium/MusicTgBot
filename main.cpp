#include "BotController.h"
#include "userdata.h"
#include "constants.h"



int main() 
{
	mb::core::changeData();
	auto *bot = mb::BotController::getInstance(mb::init::TOKEN);
	bot->initCommands(mb::init::CMDLET);
	bot->listen();
	system("pause");
}