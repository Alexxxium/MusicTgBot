#pragma once
#include "Command.h"


namespace mb::cmd::any
{
	// Return command-handler (checking previos invoke command and chousing handler). WARNING: Can return NULL!
	Command* getHandler(TgBot::Message::Ptr &message, std::unordered_map<int64_t, std::string> &buffer);

	bool isValidFile(TgBot::Message::Ptr message, TgBot::Bot &bot);


	class CreatePlayList: public AnyCommand
	{
	public:
		CreatePlayList() = delete;
		~CreatePlayList() = default;
		explicit CreatePlayList(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): AnyCommand(name, message) {}
		Command* clone() const noexcept override { return new CreatePlayList(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	
	class RenamePlayList: public AnyCommand
	{
	public:
		RenamePlayList() = delete;
		~RenamePlayList() = default;
		explicit RenamePlayList(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): AnyCommand(name, message) {}
		Command* clone() const noexcept override { return new RenamePlayList(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}