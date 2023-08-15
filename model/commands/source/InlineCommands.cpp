#include "InlineCommands.h"


namespace mb::cmd::inl
{
	bool PlayLists::execute(TgBot::Bot &bot) const {
		std::cout << "Inline execute:\t" << _query->data << '\n';
		return true;
	}

	bool AddPlaylistPressed::execute(TgBot::Bot &bot) const {
		return true;
	}
}
