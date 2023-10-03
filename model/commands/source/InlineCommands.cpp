#include "InlKeyboardFactory.h"
#include "InlineCommands.h"
#include "BotController.h"
#include "MacroCommands.h"
#include "validators.h"
#include "constants.h"
#include "userdata.h"
#include <filesystem>



static const std::string lockSection = mb::core::parseHTML(mb::pth::MESSAGE_DIR + mb::pth::HTML_LOCK_SECTION);
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

		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		if (core::checkLock(id, data)) {
			bot.getApi().sendMessage(id, lockSection, false, 0, nullptr, mrk::HTML);
			return false;
		}

		bot.getApi().sendMessage(id, text, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool RemovePListPressed::execute(TgBot::Bot &bot) const {
		constexpr auto tag_ = "<i>\"", _tag = "?\"</i>";
		static std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_REMOVE_MESSAGE);

		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		if (core::checkLock(id, data)) {
			bot.getApi().sendMessage(id, lockSection, false, 0, nullptr, mrk::HTML);
			return false;
		}

		const std::string &text  = html + tag_ + data + _tag;
		const auto &menu  = InlKeyboardFactory::SelectMenu_YN(CBQ_REMOVE_PLAYLIST_YN, data);

		bot.getApi().sendMessage(id, text, false, 0, menu, mrk::HTML);
		return true;
	}

	bool UploadPListPressed::execute(TgBot::Bot &bot) const {
		constexpr auto cmd = "upload_group";
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		if (core::checkLock(id, data)) {
			bot.getApi().sendMessage(id, lockSection, false, 0, nullptr, mrk::HTML);
			return false;
		}

		auto *ctrl = BotController::getInstance();
		if (ctrl == nullptr) {
			throw err::NULL_INSTANSE;
		}

		std::string args = core::makeServerCmd(cmd, { std::to_string(id), data });
		std::string reply = ctrl->forward(args);
		core::lockToResponse(reply, id, data);

		bot.getApi().sendMessage(id, reply, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool AddTracksPressed::execute(TgBot::Bot &bot) const {
		static std::string text = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_ADDTRACKS);
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		if (core::checkLock(id, data)) {
			bot.getApi().sendMessage(id, lockSection, false, 0, nullptr, mrk::HTML);
			return false;
		}

		bot.getApi().sendMessage(_query->message->chat->id, text, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool ReturnToPLists::execute(TgBot::Bot &bot) const {
		return Execute<mcr::ShowPlayLists>::execute(NONE, _query->message, bot);
	}



	bool TrackPressed::execute(TgBot::Bot &bot) const {
		constexpr auto tag_ = "<i>\"", _tag = "\"</i>";
		static std::string header = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_HEADER_MESSAGE);

		const int64_t &id = _query->message->chat->id;
		const std::string &cback = core::suffixCmd(_query->data);
		const std::string &text  = header + tag_ + core::getTrack(id, cback) + core::getExten(id, cback) + _tag;

		auto menu = InlKeyboardFactory::TrackMenu(id, cback);
		bot.getApi().sendMessage(id, text, false, 0, menu, mrk::HTML);


		return true;
	}

	bool RenameTrackPressed::execute(TgBot::Bot &bot) const {
		static const std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_RENAME_MESSAGE);

		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		if (core::checkLock(id, data)) {
			bot.getApi().sendMessage(id, lockSection, false, 0, nullptr, mrk::HTML);
			return false;
		}

		bot.getApi().sendMessage(id, html, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool RemoveTrackPressed::execute(TgBot::Bot &bot) const {
		constexpr auto tag_ = "<i>\"", _tag = "?\"</i>";
		static std::string html = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_REMOVE_MESSAGE);

		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		if (core::checkLock(id, data)) {
			bot.getApi().sendMessage(id, lockSection, false, 0, nullptr, mrk::HTML);
			return false;
		}

		const std::string &text = html + tag_ + core::getTrack(id, data) + _tag;
		const auto &menu  = InlKeyboardFactory::SelectMenu_YN(CBQ_REMOVE_TRACK_YN, data);

		bot.getApi().sendMessage(id, text, false, 0, menu, mrk::HTML);
		return true;
	}

	bool UploadTrackPressed::execute(TgBot::Bot &bot) const {
		constexpr auto cmd = "upload";
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);

		if (core::checkLock(id, data)) {
			bot.getApi().sendMessage(id, lockSection, false, 0, nullptr, mrk::HTML);
			return false;
		}

		auto *ctrl = BotController::getInstance();
		if (ctrl == nullptr) {
			throw err::NULL_INSTANSE;
		}

		std::string args = core::makeServerCmd(cmd, { std::to_string(id), data});
		std::string reply = ctrl->forward(args);
		core::lockToResponse(reply, id, data);

		bot.getApi().sendMessage(id, reply, false, 0, nullptr, mrk::HTML);
		return true;
	}

	bool ReturnToPList::execute(TgBot::Bot &bot) const {
		return Execute<inl::PListPressed>::execute(CBQ_SHOW_PLAYLIST, _query->message, bot,
			core::makeCallback(CBQ_SHOW_PLAYLIST, core::getPList(_query->message->chat->id, core::suffixCmd(_query->data)))
		);
	}



	bool RemoveTrackPressed_YN::execute(TgBot::Bot &bot) const {
		const int64_t &id = _query->message->chat->id;
		const auto &message = _query->message;
		const std::string &lclpth  = core::suffixCmd(_query->data);
		const std::string &prevcmd = core::makeCallback(CBQ_SHOW_TRACK, core::suffixCmd(BotController::bufferEntry(id)));

		if (core::prefixCmd(lclpth) == NONE) {
			return Execute<inl::TrackPressed>::execute(CBQ_SHOW_TRACK, message, bot, prevcmd);
		}

		if (core::checkLock(id, lclpth)) {
			bot.getApi().sendMessage(id, lockSection, false, 0, nullptr, mrk::HTML);
			return false;
		}

		core::remove(id, lclpth);

		const std::string &plist = core::getPList(id, lclpth);
		const std::string &cback = core::makeCallback(CBQ_SHOW_PLAYLIST, plist);

		return Execute<inl::PListPressed>::execute(CBQ_SHOW_PLAYLIST, message, bot, cback);
	}

	bool RemovePListPressed_YN::execute(TgBot::Bot &bot) const {
		const int64_t &id = _query->message->chat->id;
		const std::string &data = core::suffixCmd(_query->data);
		const std::string &prevcmd = core::makeCallback(CBQ_SHOW_TRACK, core::suffixCmd(BotController::bufferEntry(id)));

		if (data != NONE) {
			if (core::checkLock(id, data)) {
				bot.getApi().sendMessage(id, lockSection, false, 0, nullptr, mrk::HTML);
				return false;
			}
			core::remove(id, data);
		}

		return Execute<mcr::ShowPlayLists>::execute(NONE, _query->message, bot);
	}
}
