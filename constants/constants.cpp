#include "MacroCommands.h"
#include "InlineCommands.h"
#include "constants.h"


const std::string TOKEN = "6282754512:AAFaF5Gfi3uTTgNRndN8y3c3xac2y7b-25U";



namespace markup
{
	const std::string MARKDOWN = "Murkdown", HTML = "HTML";
}

namespace cmd::type
{
	const std::string MACRO = "MACRO", INLINE = "INLINE", ANY = "ANY";
}

namespace err
{
	std::exception 
		EMBARGO("This code area is banned!"),
		CANT_OPEN_HTML("Can`t open file.html!");
}

namespace path
{
	const std::string MARKUP_DIR = "D:/C++ prog/MusicBot/constants/messages/", WELCOME = "welcome.html", INFO = "info.html";
}

namespace init
{
	using namespace cmd;

	const std::vector<cmd::Command*> CMD_BASE
	{
		new mcr::Start("start"),
		new mcr::Info("info"),
		new mcr::ShowPlayList("playlists"),
        new inl::PlayLists("nahyi name")
	};

	TgBot::ReplyKeyboardMarkup::Ptr initMacroKeyboard() {
		TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
		TgBot::KeyboardButton::Ptr cmd1(new TgBot::KeyboardButton); cmd1->text = "/info";
		TgBot::KeyboardButton::Ptr cmd2(new TgBot::KeyboardButton); cmd2->text = "/playlists";
		keyboard->resizeKeyboard = true;
		keyboard->oneTimeKeyboard = false;
		keyboard->keyboard = { { cmd1, cmd2 } };
		
		return keyboard;
	}
}
