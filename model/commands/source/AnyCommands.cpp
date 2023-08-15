#include "AnyCommands.h"
#include "constants.h"
#include "parsers.h"


namespace mb::cmd::any
{
	Command* getHandler(TgBot::Message::Ptr &message) 
	{
		auto &reply = message->replyToMessage;
		if (!reply) {
			return nullptr;
		}
		if (reply->text == core::parseHTML(pth::MESSAGE_DIR + pth::ADD_PLIST_MESSAGE)) {
			
		}
	}

	bool ValidatePListName::execute(TgBot::Bot &bot) const {
		return true;
	}
}