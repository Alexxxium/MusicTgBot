#include "InlKeyboardFactory.h"
#include "validators.h"
#include "constants.h"
#include "userdata.h"



namespace mb::cmd
{
	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::PlayListsMenu(const int64_t &user_id) {
		const auto &playlists = core::getPlayLists(user_id);

		TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
		TgBot::InlineKeyboardButton::Ptr addPList(new TgBot::InlineKeyboardButton);

		addPList->text         = btn::BTN_ADD_PLAYLIST;
		addPList->callbackData = core::makeCallback(CBQ_ADD_PLAYLIST, NONE);

		if (playlists.empty()) {
			TgBot::InlineKeyboardButton::Ptr emptBtn(new TgBot::InlineKeyboardButton);
			emptBtn->text            = btn::BTN_EMPTY_PLAYLISTS;
			emptBtn->callbackData    = core::makeCallback(NONE, NONE);
			keyboard->inlineKeyboard = { { emptBtn }, { addPList } };
			return keyboard;
		}

		for (const auto &plist_name: playlists) {
			TgBot::InlineKeyboardButton::Ptr plist(new TgBot::InlineKeyboardButton);
			plist->text         = plist_name;
			plist->callbackData = core::makeCallback(CBQ_SHOW_PLAYLIST, plist_name);
			keyboard->inlineKeyboard.push_back({ plist });
		}

		keyboard->inlineKeyboard.push_back({ addPList });

		return keyboard;
	}

	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::PlayListMenu(const int64_t &user_id, const std::string &playlist_name) {
		const auto &playlist = core::getPlayList(user_id, playlist_name);

		TgBot::InlineKeyboardMarkup::Ptr keyboard (new TgBot::InlineKeyboardMarkup);
		TgBot::InlineKeyboardButton::Ptr addbtn   (new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr renamebtn(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr removebtn(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr uploadbtn(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr returnbtn(new TgBot::InlineKeyboardButton);

		addbtn->text    = btn::BTN_ADD;
		renamebtn->text = btn::BTN_RENAME;
		removebtn->text = btn::BTN_REMOVE;
		uploadbtn->text = btn::BTN_UPLOAD;
		returnbtn->text = btn::BTN_RETURN;

		addbtn->callbackData    = core::makeCallback(CBQ_ADD_TRACKS,      playlist_name);
		renamebtn->callbackData = core::makeCallback(CBQ_RENAME_PLAYLIST, playlist_name);
		removebtn->callbackData = core::makeCallback(CBQ_REMOVE_PLAYLIST, playlist_name);
		uploadbtn->callbackData = core::makeCallback(CBQ_UPLOAD_PLAYLIST, playlist_name);
		returnbtn->callbackData = core::makeCallback(CBQ_RETURN_TO_PLAYLISTS, playlist_name);

		if (playlist.empty()) {
			TgBot::InlineKeyboardButton::Ptr emptBtn(new TgBot::InlineKeyboardButton);
			emptBtn->text            = btn::BTN_EMPTY_PLAYLIST;
			emptBtn->callbackData    = core::makeCallback(NONE, NONE);
			uploadbtn->callbackData  = core::makeCallback(NONE, NONE);
			keyboard->inlineKeyboard = { { emptBtn }, { renamebtn, removebtn }, { addbtn, uploadbtn }, { returnbtn } };
			return keyboard;
		}
		for (const auto &track_name: playlist) {
			TgBot::InlineKeyboardButton::Ptr track(new TgBot::InlineKeyboardButton);
			std::string local_path = core::makePath({ playlist_name, track_name });
			track->text            = track_name;
			track->callbackData    = core::makeCallback(CBQ_SHOW_TRACK, local_path);
			keyboard->inlineKeyboard.push_back({ track });
		}

		keyboard->inlineKeyboard.push_back({ renamebtn, removebtn });
		keyboard->inlineKeyboard.push_back({ addbtn, uploadbtn });
		keyboard->inlineKeyboard.push_back({ returnbtn });
		
		return keyboard;
	}

	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::TrackMenu(const int64_t &user_id, const std::string &track_locpth) {
		if (!core::exists(user_id, track_locpth)) {
			throw err::NOT_EXISTED_TRACK;
		}

		TgBot::InlineKeyboardMarkup::Ptr keyboard (new TgBot::InlineKeyboardMarkup);
		TgBot::InlineKeyboardButton::Ptr trackbtn (new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr renamebtn(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr removebtn(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr uploadbtn(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr returnbtn(new TgBot::InlineKeyboardButton);

		trackbtn->text  = core::getTrack(user_id, track_locpth);
		renamebtn->text = btn::BTN_RENAME;
		removebtn->text = btn::BTN_REMOVE;
		uploadbtn->text = btn::BTN_UPLOAD;
		returnbtn->text = btn::BTN_RETURN;
		trackbtn->callbackData  = core::makeCallback(CBQ_UPLOAD_TRACK, track_locpth);
		renamebtn->callbackData = core::makeCallback(CBQ_RENAME_TRACK, track_locpth);
		removebtn->callbackData = core::makeCallback(CBQ_REMOVE_TRACK, track_locpth);
		uploadbtn->callbackData = core::makeCallback(CBQ_UPLOAD_TRACK, track_locpth);
		returnbtn->callbackData = core::makeCallback(CBQ_RETURN_TO_PLAYLIST, track_locpth);

		keyboard->inlineKeyboard = {
			{ trackbtn },
			{ renamebtn, removebtn },
			{ uploadbtn, returnbtn }
		};

		return keyboard;
	}

	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::SelectMenu_YN(types inlcmd, const std::string &yes_callbackdata) {
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
