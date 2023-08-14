#include "MacroCommands.h"
#include "InlKeyboardFactory.h"
#include "constants.h"
#include "parsers.h"

namespace cmd::mcr
{
	bool Start::execute(TgBot::Bot &bot) const {
		log();

		std::string html = std::move(core::parseHTML(path::MARKUP_DIR + path::WELCOME));
		bot.getApi().sendMessage(_message->chat->id, html, false, 0, init::initMacroKeyboard(), markup::HTML);

		return true;
	}

	bool Info::execute(TgBot::Bot &bot) const {
		log();

		std::string html = std::move(core::parseHTML(path::MARKUP_DIR + path::INFO));
		bot.getApi().sendMessage(_message->chat->id, html, false, 0, nullptr, markup::HTML);

		return true;
	}

	bool ShowPlayList::execute(TgBot::Bot &bot) const {
		log();
		board::InlKeyboardFactory obj(_message->chat->id);
		auto keyboard = obj.PlayLists();
		bot.getApi().sendMessage(_message->chat->id, "Playlist:", false, 0, keyboard, markup::HTML);

		return true;
	}

	bool CreatePlayList::execute(TgBot::Bot &bot) const {
		log();



		return true;
	}
}