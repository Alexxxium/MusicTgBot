#pragma once
#include "Command.h"


namespace mb::cmd::inl
{
	class PlayListPressed: public InlineCommand
	{
	public:
		explicit PlayListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new PlayListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class AddPlaylistPressed: public InlineCommand
	{
	public:
		explicit AddPlaylistPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new AddPlaylistPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};


	class TrackPressed: public InlineCommand
	{
	public:
		explicit TrackPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new TrackPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RenamePListPressed: public InlineCommand
	{
	public:
		explicit RenamePListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RenamePListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RemovePListPressed: public InlineCommand
	{
	public:
		explicit RemovePListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RemovePListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class AddTracksPressed: public InlineCommand
	{
	public:
		explicit AddTracksPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new AddTracksPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class UploadPListPressed: public InlineCommand
	{
	public:
		explicit UploadPListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new UploadPListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};


	class RenameTrackPressed: public InlineCommand
	{
	public:
		explicit RenameTrackPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RenameTrackPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

/// Yes/No menu to remove playlist 
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
