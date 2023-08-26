#include "InlineCommands.h"
#include "InlKeyboardFactory.h"
#include "MacroCommands.h"
#include "constants.h"
#include "validators.h"
#include "userdata.h"


namespace mb::cmd::inl
{
	bool PlayListPressed::execute(TgBot::Bot &bot) const {
		log();

		constexpr auto bi_s = "<b><i>", bi_e = "</i></b>";

		const int64_t &id = _query->message->chat->id;
		const std::string data = core::suffixCmd(_query->data);
	    const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_PLIST_HEADER) + bi_s + data + bi_e;
		TgBot::InlineKeyboardMarkup::Ptr board;

		return core::protectedShell(id, bot, [&]() {
			bot.getApi().sendMessage(id, html, false, 0, InlKeyboardFactory::PlayListMenu(id, data), mrk::HTML);
		});
	}

	bool AddPlaylistPressed::execute(TgBot::Bot &bot) const {
		log();

		auto html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_ADD_PLIST_MESSAGE);
		bot.getApi().sendMessage(_query->message->chat->id, html, false, 0, nullptr, mrk::HTML);

		return true;
	}

	bool TrackPressed::execute(TgBot::Bot &bot) const {
		log();
		bot.getApi().sendMessage(_query->message->chat->id,
			core::suffixCmd(_query->data),
			false,
			0,
			InlKeyboardFactory::TrackMenu(_query->message->chat->id, core::suffixCmd(_query->data)),
			mrk::HTML
		);
		return true;
	}

	bool RenamePListPressed::execute(TgBot::Bot &bot) const {
		log();

		const int64_t &id = _query->message->chat->id;
		const std::string data = core::suffixCmd(_query->data);
		const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_ADD_PLIST_MESSAGE);
		bot.getApi().sendMessage(id, html, false, 0, nullptr, mrk::HTML);

		return true;
	}

	bool RemovePListPressed::execute(TgBot::Bot &bot) const {
		log();

		constexpr auto bi_s = "<b><i>", bi_e = "</i></b>", wh = "?";

		const int64_t &id = _query->message->chat->id;
		const std::string data = core::suffixCmd(_query->data);

		const auto board = InlKeyboardFactory::SelectMenu_YN(CBQ_SELECT_YN, data);
		const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_SELECT_YN_PLIST) + bi_s + data + wh + bi_e;

		bot.getApi().sendMessage(id, html, false, 0, board, mrk::HTML);

		return true;
	}

	bool AddTracksPressed::execute(TgBot::Bot &bot) const {
		log();
		return true;
	}

	bool UploadPListPressed::execute(TgBot::Bot &bot) const {
		log();
		return true;
	}


	bool RemovePListPressed_YN::execute(TgBot::Bot &bot) const {
		log();

		const int64_t &id = _query->message->chat->id;
		const std::string cback = core::suffixCmd(_query->data);

		const auto reserver = [&]() {
			std::unique_ptr<Command> plists(new mcr::ShowPlayLists(std::to_string(NONE)));
			plists->setMessage(_query->message);
			plists->execute(bot);
			
		};

		if (cback == NONE) {
			reserver();
			return true;
		}

		return core::protectedShell(id, bot, [&]() {
			core::removePlayList(id, cback);
			reserver();
		});
	}
}
