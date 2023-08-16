#pragma once
#include "Command.h"


namespace mb::cmd::any
{
	Command* getHandler(TgBot::Message::Ptr &message, std::unordered_map<int64_t, std::string> &buffer);


	class CreatePlayList: public AnyCommand
	{
	public:
		CreatePlayList() = delete;
		~CreatePlayList() = default;
		explicit CreatePlayList(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): AnyCommand(name, message) {}
		Command* clone() const noexcept override { return new CreatePlayList(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}