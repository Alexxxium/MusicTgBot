#include "InlKeyboardFactory.h"
#include "constants.h"
#include "userdata.h"
#include "parsers.h"


namespace mb::cmd
{
	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::PlayLists(const int64_t &user_id) 
	{
		const auto &playlists = core::getUserPlaylists(user_id);

		TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
		TgBot::InlineKeyboardButton::Ptr addPlist(new TgBot::InlineKeyboardButton);

		addPlist->text = btn::BTN_ADD_PLAYLIST;
		addPlist->callbackData = core::makeCallback(CBQ_ADD_PLAYLIST, NONE);
		

		if (playlists.empty()) {
			TgBot::InlineKeyboardButton::Ptr emptBtn(new TgBot::InlineKeyboardButton);

			emptBtn->text = btn::BTN_EMPTY_PLAYLIST;
			emptBtn->callbackData = core::makeCallback(NONE, NONE);
			keyboard->inlineKeyboard = { { emptBtn }, { addPlist } };
			return keyboard;
		}

		for (const auto &plist_name: playlists) {
			TgBot::InlineKeyboardButton::Ptr plist(new TgBot::InlineKeyboardButton);

			plist->text = plist_name;
			plist->callbackData = core::makeCallback(CBQ_SHOW_PLAYLIST, plist_name);
			keyboard->inlineKeyboard.push_back({ plist });
		}

		keyboard->inlineKeyboard.push_back({ addPlist });

		return keyboard;
	}

	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::TrackMenu(const int64_t &user_id, const std::string &track_name) {
		/// create keyboard with concreate track in PlayList
		return nullptr;
	}

	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::Tracks(const int64_t &user_id, const std::string &play_list_name) {
		/// create keyboard with all tracks in PlayList
		return nullptr;
	}
}
