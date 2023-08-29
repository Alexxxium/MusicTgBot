#include "InlineCommands.h"
#include "InlKeyboardFactory.h"
#include "BotController.h"
#include "MacroCommands.h"
#include "constants.h"
#include "validators.h"
#include "userdata.h"

#include <filesystem>



namespace mb::cmd::inl
{
	namespace fs = std::filesystem;


	bool PlayListPressed::execute(TgBot::Bot &bot) const {
		log();
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		constexpr auto bi_s = "<i>\"", bi_e = "\"</i>";
		const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_PLIST_HEADER) + bi_s + data + bi_e;

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
		const std::string &cback = core::suffixCmd(_query->data);

		constexpr auto bi_s = "<i>\"", bi_e = "\"</i>";
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

	
	bool RemovePListPressed::execute(TgBot::Bot &bot) const {
		log();
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);
		static const std::string text = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_SELECT_YN_PLIST);

		const auto &board = InlKeyboardFactory::SelectMenu_YN(CBQ_REMOVE_PLAYLIST_YN, data);

		constexpr auto bi_s = "<i>\"", bi_e = "\"</i>", wh = "?";
		const std::string html = text + bi_s + data + wh + bi_e;

		bot.getApi().sendMessage(id, html, false, 0, board, mrk::HTML);
		return true;
	}

	bool RemovePListPressed_YN::execute(TgBot::Bot &bot) const {
		log();
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		if (data == NONE) {
			return Execute<mcr::ShowPlayLists>::execute(NONE, _query->message, bot);
		}
		core::remove(id, data);
		return Execute<mcr::ShowPlayLists>::execute(NONE, _query->message, bot);
	}

	bool RemoveTrackPressed::execute(TgBot::Bot &bot) const {
		log();
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);
		static const std::string text = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_SELECT_YN_TACK);

		const auto &board = InlKeyboardFactory::SelectMenu_YN(CBQ_REMOVE_TRACK_YN, data);

		constexpr auto bi_s = "<i>\"", bi_e = "\"</i>", wh = "?";
		const std::string html = text + bi_s + fs::path(data).stem().string() + wh + bi_e;

		bot.getApi().sendMessage(id, html, false, 0, board, mrk::HTML);
		return true;
	}

	bool RemoveTrackPressed_YN::execute(TgBot::Bot &bot) const {
		log();
		const int64_t &id = _query->message->chat->id;
		const std::string &cback = core::suffixCmd(_query->data);

		auto t = core::suffixCmd(BotController::bufferEntry(id));

		if (core::prefixCmd(cback) == NONE) {
			return Execute<inl::TrackPressed>::execute(CBQ_SHOW_TRACK, _query->message, bot, core::makeCallback(CBQ_SHOW_TRACK, t));
		}
		core::remove(id, cback);
		std::string plist = *(core::splitPath(cback).begin());
		return Execute<inl::PlayListPressed>::execute(CBQ_SHOW_PLAYLIST, _query->message, bot, core::makeCallback(CBQ_SHOW_PLAYLIST, plist));
	}
}
