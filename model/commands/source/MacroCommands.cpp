#include "InlKeyboardFactory.h"
#include "MacroCommands.h"
#include "constants.h"
#include "parsers.h"


namespace mb::cmd::mcr
{
	bool Start::execute(TgBot::Bot &bot) const {
		log();

		std::string html = std::move(core::parseHTML(pth::MESSAGE_DIR + pth::WELCOME));
		bot.getApi().sendMessage(_message->chat->id, html, false, 0, init::initMacroKeyboard(), mrk::HTML);

		return true;
	}

	bool Info::execute(TgBot::Bot &bot) const {
		log();

		std::string html = std::move(core::parseHTML(pth::MESSAGE_DIR + pth::INFO));
		bot.getApi().sendMessage(_message->chat->id, html, false, 0, nullptr, mrk::HTML);

		return true;
	}

	bool ShowPlayLists::execute(TgBot::Bot &bot) const {
		log();

		auto board = InlKeyboardFactory::PlayLists(_message->chat->id);
		std::string header = core::parseHTML(pth::MESSAGE_DIR + pth::PLISTS_HEADER);
		bot.getApi().sendMessage(_message->chat->id, header, false, 0, board, mrk::HTML);

		return true;
	}
}
