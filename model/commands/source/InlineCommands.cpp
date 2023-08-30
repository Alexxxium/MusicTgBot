#include "InlineCommands.h"
#include "InlKeyboardFactory.h"
#include "BotController.h"
#include "MacroCommands.h"
#include "constants.h"
#include "validators.h"
#include "userdata.h"

#include <filesystem>



namespace fs = std::filesystem;

namespace mb::cmd::inl
{
	bool AddPListPressed::execute(TgBot::Bot &bot) const {
		constexpr int8_t maxlen = 60;
		const int64_t &id = _query->message->chat->id;

		static std::string 
			text  = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_RENAME_MESSAGE),
			bound = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_MAX_COUNT_MESSAGE);

		if (core::countPLists(id) > maxlen) {
			bot.getApi().sendMessage(id, bound, false, 0, nullptr, mrk::HTML);
			return false;
		}

		bot.getApi().sendMessage(id, text, false, 0, nullptr, mrk::HTML);
		return true;
	}



	bool PListPressed::execute(TgBot::Bot &bot) const {
		constexpr auto tag_ = "<i>\"", _tag = "\"</i>";
		static std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_HEADER_MESSAGE);

		const std::string &data = core::suffixCmd(_query->data);
		const std::string &text = html + tag_ + data + _tag;

		const int64_t &id = _query->message->chat->id;
		const auto &menu  = InlKeyboardFactory::PlayListMenu(id, data);

		bot.getApi().sendMessage(id, text, false, 0, menu, mrk::HTML);
		return true;
	}

	bool RenamePListPressed::execute(TgBot::Bot &bot) const {
		static std::string text = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_RENAME_MESSAGE);	

		bot.getApi().sendMessage(_query->message->chat->id, text, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool RemovePListPressed::execute(TgBot::Bot &bot) const {
		constexpr auto tag_ = "<i>\"", _tag = "?\"</i>";
		static std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_REMOVE_MESSAGE);

		const std::string &data = core::suffixCmd(_query->data);
		const std::string text  = html + tag_ + data + _tag;

		const int64_t &id = _query->message->chat->id;
		const auto &menu  = InlKeyboardFactory::SelectMenu_YN(CBQ_REMOVE_PLAYLIST_YN, data);

		bot.getApi().sendMessage(id, text, false, 0, menu, mrk::HTML);
		return true;
	}

	bool UploadPListPressed::execute(TgBot::Bot &bot) const {
		log();
		return true;
	}

	bool AddTracksPressed::execute(TgBot::Bot &bot) const {
		log();
		return true;
	}



	bool TrackPressed::execute(TgBot::Bot &bot) const {
		constexpr auto tag_ = "<i>\"", _tag = "\"</i>";
		static std::string header = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_HEADER_MESSAGE);

		const int64_t &id = _query->message->chat->id;
		const std::string &cback = core::suffixCmd(_query->data);
		const std::string &text  = header + tag_ + core::getTrack(id, cback) + _tag;

		bot.getApi().sendMessage(id, text, false, 0,
			InlKeyboardFactory::TrackMenu(id, cback), mrk::HTML);

		return true;
	}

	bool RenameTrackPressed::execute(TgBot::Bot &bot) const {
		static const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_RENAME_MESSAGE);

		bot.getApi().sendMessage(_query->message->chat->id, html, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool RemoveTrackPressed::execute(TgBot::Bot &bot) const {
		constexpr auto tag_ = "<i>\"", _tag = "?\"</i>";
		static std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_REMOVE_MESSAGE);

		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);
		const std::string &text = html + tag_ + core::getTrack(id, data) + _tag;
		const auto &menu  = InlKeyboardFactory::SelectMenu_YN(CBQ_REMOVE_TRACK_YN, data);

		bot.getApi().sendMessage(id, text, false, 0, menu, mrk::HTML);
		return true;
	}

	bool UploadTrackPressed::execute(TgBot::Bot &bot) const {
		log();
		return true;
	}



	bool RemoveTrackPressed_YN::execute(TgBot::Bot &bot) const {
		const int64_t &id = _query->message->chat->id;
		const auto &message = _query->message;
		const std::string &lclpth  = core::suffixCmd(_query->data);
		const std::string &prevcmd = core::makeCallback(CBQ_SHOW_TRACK, core::suffixCmd(BotController::bufferEntry(id)));

		if (core::prefixCmd(lclpth) == NONE) {
			return Execute<inl::TrackPressed>::execute(CBQ_SHOW_TRACK, message, bot, prevcmd);
		}

		core::remove(id, lclpth);

		const std::string &plist = core::getPList(id, lclpth);
		const std::string &cback = core::makeCallback(CBQ_SHOW_PLAYLIST, plist);

		return Execute<inl::PListPressed>::execute(CBQ_SHOW_PLAYLIST, message, bot, cback);
	}

	bool RemovePListPressed_YN::execute(TgBot::Bot &bot) const {
		const std::string &data = core::suffixCmd(_query->data);

		if (data != NONE) {
			core::remove(_query->message->chat->id, data);
		}

		return Execute<mcr::ShowPlayLists>::execute(NONE, _query->message, bot);
	}
}
