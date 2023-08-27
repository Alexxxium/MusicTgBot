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
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		constexpr auto bi_s = "<b><i>", bi_e = "</i></b>";
		static const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_PLIST_HEADER) + bi_s + data + bi_e;

		bot.getApi().sendMessage(id, html, false, 0, InlKeyboardFactory::PlayListMenu(id, data), mrk::HTML);
		return true;
	}

	bool AddPlaylistPressed::execute(TgBot::Bot &bot) const {
		log();
		constexpr int8_t maxlen = 60;
		const int64_t &id = _query->message->chat->id;

		static const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_ADD_PLIST_MESSAGE);
		static const std::string maxlen_text = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_MAX_COUNT_PLISTS);

		if (core::getPlayLists(id).size() >= maxlen) {
			bot.getApi().sendMessage(id, maxlen_text, false, 0, nullptr, mrk::HTML);
			return false;
		};
		bot.getApi().sendMessage(id, html, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool TrackPressed::execute(TgBot::Bot &bot) const {
		log();
		const int64_t &id = _query->message->chat->id;
		const std::string cback = core::suffixCmd(_query->data);

		constexpr auto bi_s = "<b><i>", bi_e = "</i></b>";
		static const std::string header = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_TRACK_HEADER);
		
		const std::string &text = header + bi_s + core::getTrack(id, cback).first + bi_e;
		bot.getApi().sendMessage(id, text, false, 0,
			InlKeyboardFactory::TrackMenu(id, cback), mrk::HTML);

		return true;
	}

	bool RenamePListPressed::execute(TgBot::Bot &bot) const {
		log();
		static const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_ADD_PLIST_MESSAGE);

		const int64_t &id = _query->message->chat->id;
		
		bot.getApi().sendMessage(id, html, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool RemovePListPressed::execute(TgBot::Bot &bot) const {
		log();
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);
		static const std::string text = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_SELECT_YN_PLIST);

		const auto &board = InlKeyboardFactory::SelectMenu_YN(CBQ_SELECT_YN, data);

		constexpr auto bi_s = "<b><i>", bi_e = "</i></b>", wh = "?";
		const std::string html = text + bi_s + data + wh + bi_e;

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


	bool RenameTrackPressed::execute(TgBot::Bot &bot) const {
		log();
		static const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_RENAME_TRACK_MESSAGE);
		bot.getApi().sendMessage(_query->message->chat->id, html, false, 0, nullptr, mrk::HTML);
		return true;
	}


	bool RemovePListPressed_YN::execute(TgBot::Bot &bot) const {
		log();
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		if (data == NONE) {
			return Execute<mcr::ShowPlayLists>::execute(NONE, _query->message, bot);
		}
		core::removePlayList(id, data);
		return Execute<mcr::ShowPlayLists>::execute(NONE, _query->message, bot);
	}
}
