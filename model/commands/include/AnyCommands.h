#pragma once
#include "Command.h"



namespace mb::cmd::any
{
	class CreatePlayList: public AnyCommand {
	public:
		explicit CreatePlayList(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): AnyCommand(name, message) {}
		Command* clone() const noexcept override { return new CreatePlayList(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RenamePlayList: public AnyCommand {
	public:
		explicit RenamePlayList(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): AnyCommand(name, message) {}
		Command* clone() const noexcept override { return new RenamePlayList(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RenameTrack: public AnyCommand{
	public:
		explicit RenameTrack(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()) : AnyCommand(name, message) {}
		Command* clone() const noexcept override { return new RenameTrack(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}
