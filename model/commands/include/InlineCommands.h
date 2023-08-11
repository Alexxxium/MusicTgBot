#pragma once
#include "Command.h"

namespace cmd::inl
{
	class PlayLists: public InlineCommand
	{
	public:
		PlayLists () = delete;
		~PlayLists() = default;
		explicit PlayLists(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new PlayLists(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}