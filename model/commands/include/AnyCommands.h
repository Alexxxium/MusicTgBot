#pragma once
#include "Command.h"


namespace mb::cmd::any
{
	Command* getHandler(TgBot::Message::Ptr &message);


	class ValidatePListName: public AnyCommand
	{
	public:
		ValidatePListName() = delete;
		~ValidatePListName() = default;
		explicit ValidatePListName(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): AnyCommand(name, message) {}
		Command* clone() const noexcept override { return new ValidatePListName(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}