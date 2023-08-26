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

		CMD_REMOVE_PLAYLIST,

		CBQ_ADD_PLAYLIST,
		CBQ_SHOW_PLAYLIST,

		CBQ_REMOVE_PLAYLIST,
		CBQ_ADD_TRACKS,
		CBQ_RENAME_PLAYLIST,
		CBQ_UPLOAD_PLAYLIST,
		CBQ_SHOW_TRACK,

		CBQ_SELECT_YN,
	};


/// MARKUP TYPES:
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

			BTN_EMPTY_PLAYLISTS,
			BTN_ADD_PLAYLIST,

			BTN_REMOVE_PLAYLIST,
			BTN_ADD_TRACKS,
			BTN_RENAME_PLAYLIST,
			BTN_UPLOAD_PLAYLIST;
	};


/// INITIALIZE DATA AND COMMANDLET:
	class init {
	public:
		static const std::string TOKEN;
		static const std::vector<cmd::Command*> CMDLET;
		static TgBot::ReplyKeyboardMarkup::Ptr  initMacroKeyboard();
	};


/// ERRORS:
	class BotError: public std::exception
	{
	public:
		BotError() = default;
		~BotError() = default;
		BotError(BotError&&) = delete;
		BotError(const BotError&) = default;
		BotError& operator=(BotError&&) = delete;
		BotError& operator=(const BotError&) = default;

		explicit BotError(const std::string &err_name);
		explicit BotError(const char *err_name);
	};

	class err {
	public:
		static const BotError
			EMBARGO,
			CANT_OPEN_TXT_FILE,
			CANT_OPEN_HTML_FILE,
			CANT_RENAME_PLAYLIST,
			NOT_EXISTED_PLAYLIST,
			NULL_CMD_PTR,
			UNKNOWN_CMD;
	};


/// CONSTANTS OF PATHS:
	class pth {
	public:
		static const std::string
			USER_DATA_DIR,
			MESSAGE_DIR,
			BUFFER_DIR,

			HTML_WELCOME,
			HTML_INFO,

			HTML_PLISTS_HEADER,
			HTML_ADD_PLIST_MESSAGE,

			HTML_LITTLE_PLIST_NAME,
			HTML_LARGE_PLIST_NAME,
			HTML_EXISTED_PLIST_NAME,
			HTML_UNCORRECT_PLIST_NAME,
			HTML_CREATED_PLIST,

			HTML_PLIST_HEADER,

			HTML_SELECT_YN_PLIST,
			
			HTML_OLD_DATA;
	};

	bool operator==(types type, const std::string &str);
	bool operator!=(types type, const std::string &str);
	bool operator==(const std::string &str, types type);
	bool operator!=(const std::string &str, types type);
}
