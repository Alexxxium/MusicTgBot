#include "ServerOperations.h"
#include <string>
#include <tgbot/tgbot.h>



namespace srv {

	void SendAudio::execute(const std::vector<std::string> &args) const {
		TgBot::Bot bot("6282754512:AAFaF5Gfi3uTTgNRndN8y3c3xac2y7b-25U");
		bot.getApi().sendMessage(710890997, "from server");
	}

}

