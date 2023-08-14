#include "InlineCommands.h"

namespace cmd::inl
{
	bool PlayLists::execute(TgBot::Bot &bot) const {
		std::cout << "Inline execute:\t" << _query->data << '\n';
		return true;
	}
}