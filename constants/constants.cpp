#include "constants.h"
#include "MacroCommands.h"
#include "InlineCommands.h"


namespace mb 
{
	using namespace cmd;


	const std::string 
		mrk::MARKDOWN = "Markup",
		mrk::HTML     = "HTML";



	const std::string
		btn::CMD_BTN_START       = "/start",
		btn::CMD_BTN_INFO        = "/info",
		btn::CMD_BTN_PLAYLISTS   = "/playlists",
		btn::BTN_EMPTY_PLAYLIST  = u8"Плейлист пуст",
		btn::BTN_ADD_PLAYLIST    = u8"Добавить плейлист",
		btn::BTN_REMOVE_PLAYLIST = u8"Удалить плейлист",
		btn::BTN_ADD_TRACK       = u8"Добавить трек";


	
	const std::exception
		err::EMBARGO             ("This code area is banned!"),
		err::CANT_OPEN_HTML_FILE ("Can`t open file.html!"),
		err::CANT_OPEN_TXT_FILE  ("Cant`t open file.txt!");



	const std::string
		pth::USER_DATA_DIR = u8"D:/C++ prog/MusicTgBot/test data/",
		pth::MESSAGE_DIR   = u8"D:/C++ prog/MusicTgBot/constants/messages/",
		pth::BUFFER_DIR    = u8"D:/C++ prog/MusicTgBot/test data/buffer/",
		pth::WELCOME_FILE  = u8"welcome.html",
		pth::INFO_FILE     = u8"info.html";



	const std::string init::TOKEN = "6282754512:AAFaF5Gfi3uTTgNRndN8y3c3xac2y7b-25U";

	const std::vector<cmd::Command*> init::CMD_BASE {
		new mcr::Start("start"),
			new mcr::Info("info"),
	};

	TgBot::ReplyKeyboardMarkup::Ptr init::initMacroKeyboard() {
		TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
		TgBot::KeyboardButton::Ptr info_btn(new TgBot::KeyboardButton);
		TgBot::KeyboardButton::Ptr plists_btn(new TgBot::KeyboardButton);
		info_btn->text = btn::CMD_BTN_INFO;
		plists_btn->text = btn::CMD_BTN_PLAYLISTS;
		keyboard->resizeKeyboard = true;
		keyboard->oneTimeKeyboard = false;
		keyboard->keyboard = { { info_btn, plists_btn } };

		return keyboard;
	}
}
