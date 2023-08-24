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


	class TrackPressed: public InlineCommand
	{
	public:
		TrackPressed() = delete;
		~TrackPressed() = default;
		explicit TrackPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new TrackPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RenamePListPressed: public InlineCommand
	{
	public:
		RenamePListPressed() = delete;
		~RenamePListPressed() = default;
		explicit RenamePListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RenamePListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RemovePListPressed: public InlineCommand
	{
	public:
		RemovePListPressed() = delete;
		~RemovePListPressed() = default;
		explicit RemovePListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RemovePListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class AddTracksPressed: public InlineCommand
	{
	public:
		AddTracksPressed() = delete;
		~AddTracksPressed() = default;
		explicit AddTracksPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new AddTracksPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class UploadPListPressed: public InlineCommand
	{
	public:
		UploadPListPressed() = delete;
		~UploadPListPressed() = default;
		explicit UploadPListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new UploadPListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};


	class RemovePListPressed_YN: public InlineCommand
	{
	public:
		RemovePListPressed_YN() = delete;
		~RemovePListPressed_YN() = default;
		explicit RemovePListPressed_YN(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RemovePListPressed_YN(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}
