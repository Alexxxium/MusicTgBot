#include "InlineCommands.h"

namespace cmd::inl
{
	bool PlayLists::execute(TgBot::Bot &bot) const {
		std::cout << _query->data << ' ';
		return true;
	}
}