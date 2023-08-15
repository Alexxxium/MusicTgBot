#pragma once
#include "Command.h"


namespace mb::cmd::inl
{
	class PlayListPressed: public InlineCommand
	{
	public:
		PlayListPressed () = delete;
		~PlayListPressed() = default;
		explicit PlayListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new PlayListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class AddPlaylistPressed: public InlineCommand
	{
	public:
		AddPlaylistPressed() = delete;
		~AddPlaylistPressed() = default;
		explicit AddPlaylistPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new AddPlaylistPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}
