#include "InlineCommands.h"
#include "MacroCommands.h"
#include "AnyCommands.h"
#include "validators.h"
#include "constants.h"
#include "userdata.h"



namespace mb::cmd::any
{
	bool CreatePlayList::execute(TgBot::Bot &bot) const {
		const int64_t &id = _message->chat->id;
		const std::string &plist = _message->text;

		if (!core::isValidPath(plist, pth::SUB_DIR_TO_PLIST, id, bot)) {
			return false;
		}

		core::create(id, plist);

		bot.getApi().sendMessage(id, core::parseHTML(pth::MESSAGE_DIR + pth::HTML_CREATED_PLIST), false, 0, nullptr, mrk::HTML);
		return Execute<mcr::ShowPlayLists>::execute(name(), _message, bot);
	}

	bool RenamePlayList::execute(TgBot::Bot &bot) const {
		const int64_t &id = _message->chat->id;
		const std::string &plist = _message->text;

		if (!core::isValidPath(plist, pth::SUB_DIR_TO_PLIST, id, bot)) {
			return false;
		}

		core::rename(id, _name, plist);

		return Execute<inl::PListPressed>::execute(CBQ_SHOW_PLAYLIST, _message, bot, 
			core::makeCallback(CBQ_SHOW_PLAYLIST, plist)
		);
	}

	bool RenameTrack::execute(TgBot::Bot &bot) const {
		const std::string
			&track = _message->text,
			&oldtr = _name,
			&newtr = core::replace(oldtr, track);
		const int64_t &id = _message->chat->id;


		if (!core::isValidPath(newtr, pth::SUB_DIR_TO_TRACK, id, bot)) {
			return false;
		}

		core::rename(id, oldtr, newtr);

		return Execute<inl::TrackPressed>::execute(track, _message, bot, 
			core::makeCallback(CBQ_SHOW_TRACK, newtr)
		);
	}
}
