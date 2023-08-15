#pragma once
#include "Command.h"


namespace mb
{
/// COMMANDS ID (CBQ - CallBack Query, не сво):
	enum types {
		NONE,
		CMD_TYPE_ANY,
		CMD_TYPE_MACRO,
		CMD_TYPE_INLINE,

		CBQ_ADD_PLAYLIST,
		CBQ_SHOW_PLAYLIST,
	};


/// MARKUPS TYPES:
	class mrk {
	public:
		static const std::string
			MARKDOWN,
			HTML;
	};


/// TEXT IN TG BUTTONS:
	class btn {
	public:
		static const std::string
			CMD_BTN_START,
			CMD_BTN_INFO,
			CMD_BTN_PLAYLISTS,
			BTN_EMPTY_PLAYLIST,
			BTN_ADD_PLAYLIST,
			BTN_REMOVE_PLAYLIST,
			BTN_ADD_TRACK;
	};


/// INITIALIZE DATA:
	class init {
	public:
		static const std::string TOKEN;
		static const std::vector<cmd::Command*> CMD_BASE;
		static TgBot::ReplyKeyboardMarkup::Ptr initMacroKeyboard();
	};


/// ERRORS:
	class err {
	public:
		static const std::exception
			EMBARGO,
			CANT_OPEN_TXT_FILE,
			CANT_OPEN_HTML_FILE;
	};


/// CONSTANTS OF PATHS:
	class pth {
	public:
		static const std::string
			USER_DATA_DIR,
			MESSAGE_DIR,
			BUFFER_DIR,
			WELCOME_FILE,
			INFO_FILE;
	};
}
