#include "MacroCommands.h"
#include "constants.h"
#include "parsers.h"


namespace mb::cmd::mcr
{
	bool Start::execute(TgBot::Bot &bot) const {
		log();

		std::string html = std::move(core::parseHTML(pth::MESSAGE_DIR + pth::WELCOME_FILE));
		bot.getApi().sendMessage(_message->chat->id, html, false, 0, init::initMacroKeyboard(), mrk::HTML);

		return true;
	}

	bool Info::execute(TgBot::Bot &bot) const {
		log();

		std::string html = std::move(core::parseHTML(pth::MESSAGE_DIR + pth::INFO_FILE));
		bot.getApi().sendMessage(_message->chat->id, html, false, 0, nullptr, mrk::HTML);

		return true;
	}

	bool ShowPlayList::execute(TgBot::Bot &bot) const {
		log();
		return true;
	}
}
