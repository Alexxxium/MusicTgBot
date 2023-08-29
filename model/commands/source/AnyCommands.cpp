#include "InlineCommands.h"
#include "MacroCommands.h"
#include "AnyCommands.h"
#include "validators.h"
#include "constants.h"
#include "userdata.h"




namespace mb::cmd::any
{
	bool CreatePlayList::execute(TgBot::Bot &bot) const
	{
		if (!core::isValidPlaylist(_message->text, _message, bot)) {
			return false;
		}
		core::create(_message->chat->id, _message->text);

		bot.getApi().sendMessage(_message->chat->id, core::parseHTML(pth::MESSAGE_DIR + pth::HTML_CREATED_PLIST), false, 0, nullptr, mrk::HTML);
		return Execute<mcr::ShowPlayLists>::execute(name(), _message, bot);
	}

	bool RenamePlayList::execute(TgBot::Bot &bot) const {
		if (!core::isValidPlaylist(_message->text, _message, bot)) {
			return false;
		}
		core::rename(_message->chat->id, _name, _message->text);
		return Execute<inl::PlayListPressed>::execute(CBQ_SHOW_PLAYLIST, _message, bot, core::makeCallback(CBQ_SHOW_PLAYLIST, _message->text));
	}

	bool RenameTrack::execute(TgBot::Bot &bot) const {
		std::string
			old_ = _name,
			new_ = core::replace(old_, _message->text);

		if (!core::isValidTrack(new_, _message, bot)) {
			return false;
		}
		core::rename(_message->chat->id, old_, new_);
		return Execute<inl::TrackPressed>::execute(_message->text, _message, bot, 
			core::makeCallback(CBQ_SHOW_TRACK, new_)
		);
	}
}
