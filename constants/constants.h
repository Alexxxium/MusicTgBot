#pragma once
#include "Command.h"
#include <unordered_set>


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
		
		CBQ_ADD_TRACKS,
		CBQ_REMOVE_PLAYLIST,
		CBQ_RENAME_PLAYLIST,
		CBQ_UPLOAD_PLAYLIST,
		CBQ_RETURN_TO_PLAYLISTS,
		CBQ_SHOW_TRACK,

		CBQ_RENAME_TRACK,
		CBQ_REMOVE_TRACK,
		CBQ_UPLOAD_TRACK,
		CBQ_RETURN_TO_PLAYLIST,

		CBQ_REMOVE_PLAYLIST_YN,
		CBQ_REMOVE_TRACK_YN,
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
			BTN_EMPTY_PLAYLIST,
			BTN_ADD_PLAYLIST,

			BTN_ADD,
			BTN_REMOVE,
			BTN_RENAME,
			BTN_UPLOAD,
			BTN_RETURN;
	};


/// INITIALIZE: TOKEN, COMMANDLET, SUPPORTED FILE FORMATS AND GLOBAL KEYBOARD
	class init {
	public:
		static const std::string TOKEN;
		static const std::vector<cmd::Command*>       CMDLET;
		static const std::unordered_set<std::string>  SUPEXT;
		static TgBot::ReplyKeyboardMarkup::Ptr        initMacroKeyboard();
	};


/// ERRORS:

	// Other errors
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

	// Old data in buttons errors
	class DataError: public std::exception {
	public:
		DataError() = default;
		~DataError() = default;
		DataError(BotError&&) = delete;
		DataError(const DataError&) = default;
		DataError& operator=(DataError&&) = delete;
		DataError& operator=(const DataError&) = default;

		explicit DataError(const std::string &err_name);
		explicit DataError(const char *err_name);
	};

	class err {
	public:
		static const BotError
			EMBARGO,
			CANT_OPEN_TXT_FILE,
			CANT_OPEN_HTML_FILE,
			CANT_RENAME_PLAYLIST,
			CANT_RENAME_TRACK,
			CANT_OPEN_LOCK_FILE,
			UNKNOWN_SUBDIR,
			UNCORREKT_PATH,

			NULL_CMD_PTR,
			UNKNOWN_CMD,

			INIT_CLIENT_FAILED,
			INIT_ADDRINFO_FAILED,
			INIT_SOCKET_FAILED,
			INIT_CONNECTION_FAILED,
			SENDING_FAILED,
			RECEVING_FAILED,
			CLOSED_CONNECTION,
			INVALID_BUFFER_SIZE,
			
			NULL_INSTANSE;

		static const DataError
			OLD_DATA,
			NOT_EXISTED_PLAYLIST,
			NOT_EXISTED_TRACK,
			NOT_EXISTED_DIR;
	};


/// CONSTANTS OF PATHS:
	class pth {
	public:
		static const std::string
// Macro commands files:
			HTML_WELCOME,
			HTML_INFO,

// Dirs:
			USER_DATA_DIR,
			MESSAGE_DIR,

// Sub dirs to sames html files:
			SUB_DIR_TO_PLIST,
			SUB_DIR_TO_TRACK,

// Same logic for view:
			HTML_LITTLE_NAME,
			HTML_LARGE_NAME,
			HTML_EXISTED_NAME,
			HTML_UNCORRECT_NAME,
			HTML_REMOVE_MESSAGE,
			HTML_RENAME_MESSAGE,
			HTML_HEADER_MESSAGE,
			HTML_MAX_COUNT_MESSAGE,
			HTML_ADDTRACKS,

// Other:
			HTML_PLISTS_HEADER,
			HTML_CREATED_PLIST,
			HTML_OLD_DATA,
			HTML_WAIT_SERVER_RESP,
			HTML_WAIT_SEND_TO_SRV,
			
			LOCK_FILE,
			HTML_LOCK_SECTION;
	};


	bool operator==(types type, const std::string &str);
	bool operator!=(types type, const std::string &str);
	bool operator==(const std::string &str, types type);
	bool operator!=(const std::string &str, types type);
}
