#include "constants.h"
#include "MacroCommands.h"
#include "InlineCommands.h"


namespace mb 
{
	using namespace cmd;


	const std::string 
		mrk::MARKDOWN                  = "Markup",
		mrk::HTML                      = "HTML";



	const std::string
		btn::CMD_BTN_START             = "/start",
		btn::CMD_BTN_INFO              = "/info",
		btn::CMD_BTN_PLAYLISTS         = "/playlists",

		btn::BTN_EMPTY_PLAYLISTS       = u8"У вас нет плейлистов!",
		btn::BTN_ADD_PLAYLIST          = u8"Добавить плейлист",

		btn::BTN_REMOVE_PLAYLIST       = u8"Удалить",
		btn::BTN_ADD_TRACKS            = u8"Добавить",
		btn::BTN_RENAME_PLAYLIST       = u8"Переименовать",
		btn::BTN_UPLOAD_PLAYLIST       = u8"Выгрузить";


	
	const std::exception
		err::EMBARGO                   ("This code area is banned!"),
		err::CANT_OPEN_HTML_FILE       ("Can`t open file.html!"),
		err::CANT_OPEN_TXT_FILE        ("Cant`t open file.txt!"),
		err::CANT_RENAME_PLAYLIST      ("Can`t rename playlist!"),
		err::NOT_EXISTED_PLAYLIST      ("Open not existed playlist!");
	 


	const std::string
		pth::USER_DATA_DIR              = u8"C:/Users/alexz/C++ prog/MusicTgBot/test data/",
		pth::MESSAGE_DIR                = u8"C:/Users/alexz/C++ prog/MusicTgBot/constants/messages/",
		pth::BUFFER_DIR                 = u8"C:/Users/alexz/C++ prog/MusicTgBot/test data/buffer/",

		pth::HTML_WELCOME               = u8"welcome.html",
		pth::HTML_INFO                  = u8"info.html",

		pth::HTML_PLISTS_HEADER         = u8"PlistsHeader.html",
		pth::HTML_ADD_PLIST_MESSAGE     = u8"AddPlistMessage.html",

		pth::HTML_LITTLE_PLIST_NAME     = u8"LittlePlistName.html",
		pth::HTML_LARGE_PLIST_NAME      = u8"LargePlistName.html",
		pth::HTML_EXISTED_PLIST_NAME    = u8"ExistedPlistName.html",
		pth::HTML_UNCORRECT_PLIST_NAME  = u8"UncorrectPlistName.html",
		pth::HTML_CREATED_PLIST         = u8"CreatedPlist.html",
		pth::HTML_PLIST_HEADER          = u8"PlistHeader.html",

		pth::HTML_SELECT_YN_PLIST       = u8"SelectYN(remove playlist).html",
		
		pth::HTML_OLD_DATA              = u8"OldData.html";



	const std::string init::TOKEN       = "6282754512:AAFaF5Gfi3uTTgNRndN8y3c3xac2y7b-25U";


	const std::vector<cmd::Command*> init::CMDLET {
		new mcr::Start                  ("start"),
		new mcr::Info                   ("info"),
		new mcr::ShowPlayLists          ("playlists"),
		new inl::PlayListPressed        (std::to_string(CBQ_SHOW_PLAYLIST)),
		new inl::AddPlaylistPressed     (std::to_string(CBQ_ADD_PLAYLIST)),
		new inl::RenamePListPressed     (std::to_string(CBQ_RENAME_PLAYLIST)),
		new inl::RemovePListPressed     (std::to_string(CBQ_REMOVE_PLAYLIST)),
		new inl::AddTracksPressed       (std::to_string(CBQ_ADD_TRACKS)),
		new inl::UploadPListPressed     (std::to_string(CBQ_UPLOAD_PLAYLIST)),
		new inl::TrackPressed           (std::to_string(CBQ_SHOW_TRACK)),
		new inl::RemovePListPressed_YN  (std::to_string(CBQ_SELECT_YN))
	};

	TgBot::ReplyKeyboardMarkup::Ptr init::initMacroKeyboard() {
		TgBot::ReplyKeyboardMarkup::Ptr keyboard  (new TgBot::ReplyKeyboardMarkup);
		TgBot::KeyboardButton::Ptr      info_btn  (new TgBot::KeyboardButton);
		TgBot::KeyboardButton::Ptr      plists_btn(new TgBot::KeyboardButton);

		info_btn->text                 = btn::CMD_BTN_INFO;
		plists_btn->text               = btn::CMD_BTN_PLAYLISTS;
		keyboard->resizeKeyboard       = true;
		keyboard->oneTimeKeyboard      = false;

		keyboard->keyboard             = { { info_btn, plists_btn } };

		return keyboard;
	}


	bool operator==(types type, const std::string &str) {
		return std::to_string(type) == str;
	}
	bool operator!=(types type, const std::string &str) {
		return std::to_string(type) != str;
	}
	bool operator==(const std::string &str, types type) {
		return type == str;
	}
	bool operator!=(const std::string &str, types type) {
		return type != str;
	}
}
