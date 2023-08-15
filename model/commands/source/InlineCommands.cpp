#include "InlineCommands.h"
#include "constants.h"
#include "parsers.h"

namespace mb::cmd::inl
{
	bool PlayListPressed::execute(TgBot::Bot &bot) const {
		std::cout << "Working \"PlayListPressed::execute...\" tail:_" << core::suffixCmd(_query->data) << "\n";
		return true;
	}

	bool AddPlaylistPressed::execute(TgBot::Bot &bot) const {
		auto html = core::parseHTML(pth::MESSAGE_DIR + pth::ADD_PLIST_MESSAGE);
		bot.getApi().sendMessage(_query->message->chat->id, html, false, 0, nullptr, mrk::HTML);
		return true;
	}
}
