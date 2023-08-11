#include "MacroCommands.h"

namespace cmd::mcr
{
	
	bool Start::execute(TgBot::Bot &bot) const {
		std::cout << "Command:\ntype:\t" << type() << "\nname:\t" << name() << "\n\n";
		return true;
	}

	bool Info::execute(TgBot::Bot &bot) const {
		std::cout << "Command:\ntype:\t" << type() << "\nname:\t" << name() << "\n\n";
		return true;
	}

	bool ShowPlayList::execute(TgBot::Bot &bot) const {
		std::cout << "Command:\ntype:\t" << type() << "\nname:\t" << name() << "\n\n";
		return true;
	}

	bool CreatePlayList::execute(TgBot::Bot &bot) const {
		std::cout << "Command:\ntype:\t" << type() << "\nname:\t" << name() << "\n\n";
		return true;
	}
}