#include "InlKeyboardFactory.h"
#include "MacroCommands.h"
#include "validators.h"
#include "constants.h"



namespace mb::cmd::mcr
{
	bool Start::execute(TgBot::Bot &bot) const {
		static const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_WELCOME);

		bot.getApi().sendMessage(_message->chat->id, html, false, 0, init::initMacroKeyboard(), mrk::HTML);
		return true;
	}

	bool Info::execute(TgBot::Bot &bot) const {
		static const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_INFO);

		bot.getApi().sendMessage(_message->chat->id, html, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool ShowPlayLists::execute(TgBot::Bot &bot) const {
		static const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_PLISTS_HEADER);
		const auto &board = InlKeyboardFactory::PlayListsMenu(_message->chat->id);

		bot.getApi().sendMessage(_message->chat->id, html, false, 0, board, mrk::HTML);
		return true;
	}
}
