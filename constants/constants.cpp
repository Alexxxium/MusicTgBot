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
		btn::BTN_EMPTY_PLAYLIST        = u8"Плейлист пуст!",
		btn::BTN_ADD_PLAYLIST          = u8"Добавить плейлист",

		btn::BTN_ADD                   = u8"Добавить",
		btn::BTN_REMOVE                = u8"Удалить",
		btn::BTN_RENAME                = u8"Переименовать",
		btn::BTN_UPLOAD                = u8"Выгрузить",
		btn::BTN_RETURN                = u8"Назад";



	BotError::BotError(const char *err_name): std::exception(err_name) {}
	BotError::BotError(const std::string &err_name): std::exception(err_name.c_str()) {}

	DataError::DataError(const char *err_name): std::exception(err_name) {}
	DataError::DataError(const std::string &err_name): std::exception(err_name.c_str()) {}
	
	

	const BotError
		err::EMBARGO                   ("This code area is banned!"),
		err::CANT_OPEN_HTML_FILE       ("Can`t open file.html!"),
		err::CANT_OPEN_TXT_FILE        ("Cant`t open file.txt!"),
		err::CANT_RENAME_PLAYLIST      ("Can`t rename playlist!"),
		err::CANT_RENAME_TRACK         ("Can`t rename track!"),
		err::CANT_OPEN_LOCK_FILE       ("Can`t open lock.txt!"),
		err::UNKNOWN_SUBDIR            ("Unknown subdirectory!"),
		err::UNCORREKT_PATH            ("Uncorrect path!"),

		err::UNKNOWN_CMD               ("Unknown Command!"),
		err::NULL_CMD_PTR              ("Command pointer is NULL!"),
		
		err::INIT_CLIENT_FAILED        ("Can't initializing client!"),
		err::INIT_ADDRINFO_FAILED      ("Can't initializing ADDRINFO struct!"),
		err::INIT_SOCKET_FAILED        ("Can`t initializing socket!"),
		err::INIT_CONNECTION_FAILED    ("Can`t initializing connection!"),
		err::SENDING_FAILED            ("Error sending message to server!"),
		err::RECEVING_FAILED           ("Error receving message from server!"),
		err::CLOSED_CONNECTION         ("Closed connection to server!"),
		err::INVALID_BUFFER_SIZE       ("Invalid client's buffer lenght!"),
		
		err::NULL_INSTANSE             ("This instanse is`t created!");

	const DataError
		err::OLD_DATA                  ("Pressed old button reffering to old data!"),
		err::NOT_EXISTED_PLAYLIST      ("Open not existed playlist!"),
		err::NOT_EXISTED_TRACK         ("Open not existed track!"),
		err::NOT_EXISTED_DIR           ("Open not existed directory!");
		
	 

	const std::string
		pth::HTML_WELCOME              = u8"welcome.html",
		pth::HTML_INFO                 = u8"info.html",

		pth::USER_DATA_DIR             = u8"user data/",
		pth::BUFFER_DIR                = u8"buffer data/",
		pth::MESSAGE_DIR               = u8"messages/",

		pth::HTML_LITTLE_NAME          = u8"LittleName.html",
		pth::HTML_LARGE_NAME           = u8"LargeName.html",
		pth::HTML_EXISTED_NAME         = u8"ExistedName.html",
		pth::HTML_UNCORRECT_NAME       = u8"UncorrectName.html",
		pth::HTML_REMOVE_MESSAGE       = u8"SelectYN(remove).html",
		pth::HTML_RENAME_MESSAGE       = u8"RenameMessage.html",
		pth::HTML_HEADER_MESSAGE       = u8"Header.html",
		pth::HTML_MAX_COUNT_MESSAGE    = u8"MaxCount.html",
		pth::HTML_ADDTRACKS            = u8"AddTracks.html",

		pth::SUB_DIR_TO_PLIST          = u8"playlist/",
		pth::SUB_DIR_TO_TRACK          = u8"track/",

		pth::HTML_PLISTS_HEADER        = u8"PlistsHeader.html",
		pth::HTML_CREATED_PLIST        = u8"CreatedPlist.html",
		pth::HTML_OLD_DATA             = u8"OldData.html",
		pth::HTML_WAIT_SERVER_RESP     = u8"WaitServerResponse.html",
		pth::HTML_WAIT_SEND_TO_SRV     = u8"WaitSendingToServer.html",
		pth::HTML_BAD_ANSWER           = u8"BadAnswer.html",
		
		pth::LOCK_FILE                 = u8"lock.txt",
		pth::HTML_LOCK_SECTION         = u8"lockSection.html";



	const std::string init::TOKEN      = "6282754512:AAFaF5Gfi3uTTgNRndN8y3c3xac2y7b-25U";


	const std::vector<cmd::Command*> init::CMDLET 
	{
// Macro commands:
		new mcr::Start                 ("start"),
		new mcr::Info                  ("info"),
		new mcr::ShowPlayLists         ("playlists"),

// Playlist inline commands:
		new inl::PListPressed          (std::to_string(CBQ_SHOW_PLAYLIST)),
		new inl::AddPListPressed       (std::to_string(CBQ_ADD_PLAYLIST)),
		new inl::RenamePListPressed    (std::to_string(CBQ_RENAME_PLAYLIST)),
		new inl::RemovePListPressed    (std::to_string(CBQ_REMOVE_PLAYLIST)),
		new inl::UploadPListPressed    (std::to_string(CBQ_UPLOAD_PLAYLIST)),
		new inl::ReturnToPLists        (std::to_string(CBQ_RETURN_TO_PLAYLISTS)),
		
// Track inline commands:
		new inl::TrackPressed          (std::to_string(CBQ_SHOW_TRACK)),
		new inl::AddTracksPressed      (std::to_string(CBQ_ADD_TRACKS)),
		new inl::RenameTrackPressed    (std::to_string(CBQ_RENAME_TRACK)),
		new inl::RemoveTrackPressed    (std::to_string(CBQ_REMOVE_TRACK)),
		new inl::UploadTrackPressed    (std::to_string(CBQ_UPLOAD_TRACK)),
		new inl::ReturnToPList         (std::to_string(CBQ_RETURN_TO_PLAYLIST)),
	
// Dialog keyboard commands:
		new inl::RemovePListPressed_YN (std::to_string(CBQ_REMOVE_PLAYLIST_YN)),
		new inl::RemoveTrackPressed_YN (std::to_string(CBQ_REMOVE_TRACK_YN))
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

	const std::unordered_set<std::string> init::SUPEXT
	{
		".mp3", ".wav", ".flac"
	};



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