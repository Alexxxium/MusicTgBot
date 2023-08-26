#include "InlKeyboardFactory.h"
#include "constants.h"
#include "userdata.h"
#include "validators.h"


namespace mb::cmd
{
	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::PlayListsMenu(const int64_t &user_id) 
	{
		const auto &playlists = core::getPlayLists(user_id);

		TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
		TgBot::InlineKeyboardButton::Ptr addPList(new TgBot::InlineKeyboardButton);

		addPList->text = btn::BTN_ADD_PLAYLIST;
		addPList->callbackData = core::makeCallback(CBQ_ADD_PLAYLIST, NONE);
		

		if (playlists.empty()) {
			TgBot::InlineKeyboardButton::Ptr emptBtn(new TgBot::InlineKeyboardButton);

			emptBtn->text = btn::BTN_EMPTY_PLAYLISTS;
			emptBtn->callbackData = core::makeCallback(NONE, NONE);
			keyboard->inlineKeyboard = { { emptBtn }, { addPList } };
			return keyboard;
		}

		for (const auto &plist_name: playlists) {
			TgBot::InlineKeyboardButton::Ptr plist(new TgBot::InlineKeyboardButton);

			plist->text = plist_name;
			plist->callbackData = core::makeCallback(CBQ_SHOW_PLAYLIST, plist_name);
			keyboard->inlineKeyboard.push_back({ plist });
		}

		keyboard->inlineKeyboard.push_back({ addPList });

		return keyboard;
	}

	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::PlayListMenu(const int64_t &user_id, const std::string &playlist_name)
	{
		constexpr auto sl = "/";
		const auto &playlist = core::getPlayList(user_id, playlist_name);

		TgBot::InlineKeyboardMarkup::Ptr keyboard   (new TgBot::InlineKeyboardMarkup);
		TgBot::InlineKeyboardButton::Ptr addTracks  (new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr renamePList(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr removePList(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr uploadPList(new TgBot::InlineKeyboardButton);

		addTracks->text   = btn::BTN_ADD_TRACKS;
		renamePList->text = btn::BTN_RENAME_PLAYLIST;
		removePList->text = btn::BTN_REMOVE_PLAYLIST;
		uploadPList->text = btn::BTN_UPLOAD_PLAYLIST;

		addTracks->callbackData   = core::makeCallback(CBQ_ADD_TRACKS, playlist_name);
		renamePList->callbackData = core::makeCallback(CBQ_RENAME_PLAYLIST, playlist_name);
		removePList->callbackData = core::makeCallback(CBQ_REMOVE_PLAYLIST, playlist_name);
		uploadPList->callbackData = core::makeCallback(CBQ_UPLOAD_PLAYLIST, playlist_name);

		if (playlist.empty()) {
			TgBot::InlineKeyboardButton::Ptr emptBtn(new TgBot::InlineKeyboardButton);

			emptBtn->text             = btn::BTN_EMPTY_PLAYLISTS;
			emptBtn->callbackData     = core::makeCallback(NONE, NONE);
			uploadPList->callbackData = core::makeCallback(NONE, NONE);

			keyboard->inlineKeyboard = { { emptBtn }, { renamePList, removePList }, { addTracks, uploadPList } };
			return keyboard;
		}
		for (const auto &track_name: playlist) {
			TgBot::InlineKeyboardButton::Ptr track(new TgBot::InlineKeyboardButton);

			track->text = track_name;
			track->callbackData = core::makeCallback(CBQ_SHOW_TRACK, playlist_name + sl + track_name);
			keyboard->inlineKeyboard.push_back({ track });
		}

		keyboard->inlineKeyboard.push_back({ renamePList, removePList });
		keyboard->inlineKeyboard.push_back({ addTracks, uploadPList });
		
		return keyboard;
	}

	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::TrackMenu(const int64_t &user_id, const std::string &track_local_path) 
	{
		TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
		TgBot::InlineKeyboardButton::Ptr track (new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr rename(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr remove(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr upload(new TgBot::InlineKeyboardButton);

		rename->text = btn::BTN_RENAME_PLAYLIST;
		remove->text = btn::BTN_REMOVE_PLAYLIST;
		upload->text = btn::BTN_UPLOAD_PLAYLIST;
		rename->callbackData = core::makeCallback(NONE, NONE);
		remove->callbackData = core::makeCallback(NONE, NONE);
		upload->callbackData = core::makeCallback(NONE, NONE);

		track->text = track_local_path;                                           // callback!!! exist file!!!
		track->callbackData = core::makeCallback(NONE, track_local_path);

		keyboard->inlineKeyboard = {
			{ track },
			{ rename, remove },
			{ upload }
		};

		return keyboard;
	}

	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::SelectMenu_YN(types inlcmd, const std::string &yes_callbackdata)
	{
		constexpr auto no = u8"Нет", yes = u8"Да";

		TgBot::InlineKeyboardButton::Ptr btnYes(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr btnNo(new TgBot::InlineKeyboardButton);

		btnNo->text  = no;
		btnYes->text = yes;

		btnNo->callbackData  = core::makeCallback(inlcmd, NONE);
		btnYes->callbackData = core::makeCallback(inlcmd, yes_callbackdata);

		TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
		keyboard->inlineKeyboard = { { btnYes, btnNo } };

		return keyboard;
	}

}
