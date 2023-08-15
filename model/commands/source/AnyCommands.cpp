#include "AnyCommands.h"
#include "constants.h"
#include "parsers.h"
#include <regex>


namespace mb::cmd::any
{
	namespace fs = std::filesystem;

	Command* getHandler(TgBot::Message::Ptr &message) 
	{
		auto &reply = message->replyToMessage;
		if (!reply) {
			return nullptr;
		}
		if (reply->text == core::parseHTML(pth::MESSAGE_DIR + pth::ADD_PLIST_MESSAGE)) {    /// text and html text <b>text</b> !!!!!!!!!!!
			return new ValidatePListName("pohyi");
		}
		return nullptr;
	}

	bool ValidatePListName::execute(TgBot::Bot &bot) const {
		constexpr auto regexstr = "^[a-zA-Z0-9_-]+$";
		std::regex valid(regexstr);

		if (std::regex_search(_message->text, valid)) {
			std::cout << "Creating playlist\n";
		}
		else {
			std::cout << "ban\n";
		}

		return true;
	}
}
