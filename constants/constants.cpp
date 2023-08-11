#include "MacroCommands.h"
#include "constants.h"

const std::string TOKEN = "6282754512:AAFaF5Gfi3uTTgNRndN8y3c3xac2y7b-25U";

namespace cmd::type
{
	const std::string MACRO = "MACRO", INLINE = "INLINE", ANY = "ANY";
}

namespace err
{
	std::exception EMBARGO("This code area is banned!");
}

namespace init
{
	/// BASE OF ALL BOT`S COMMANDS

	using namespace cmd;

	const std::vector<cmd::Command*> CMD_BASE
	{
		new mcr::Start("start"),
			new mcr::Info("info"),
			new mcr::ShowPlayList("show"),
			new mcr::CreatePlayList("create")
	};
}
