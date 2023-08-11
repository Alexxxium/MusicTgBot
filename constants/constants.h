#pragma once
#include <tgbot/tgbot.h>
#include "Command.h"
#include <exception>
#include <vector>


extern const std::string TOKEN;



namespace markup 
{
	extern const std::string MARKDOWN, HTML;
}

namespace cmd::type
{
	extern const std::string MACRO, INLINE, ANY;
}

namespace err
{
	extern std::exception EMBARGO, CANT_OPEN_HTML;
}

namespace path
{
	extern const std::string MARKUP_DIR, WELCOME, INFO;
}

namespace init
{
	/// BASE OF ALL BOT`S COMMANDS
	extern const std::vector<cmd::Command*> CMD_BASE;

	/// WRITTEN COMMANDS IN BOT
	TgBot::ReplyKeyboardMarkup::Ptr initMacroKeyboard();
}
