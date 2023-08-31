#pragma once
#include "Command.h"



namespace mb::cmd::inl
{
	class AddPListPressed: public InlineCommand
	{
	public:
		explicit AddPListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()) : InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new AddPListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};



	class PListPressed: public InlineCommand
	{
	public:
		explicit PListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()) : InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new PListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
	
	class RenamePListPressed: public InlineCommand
	{
	public:
		explicit RenamePListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RenamePListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RemovePListPressed: public InlineCommand {
	public:
		explicit RemovePListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()) : InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RemovePListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class UploadPListPressed: public InlineCommand
	{
	public:
		explicit UploadPListPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()) : InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new UploadPListPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class AddTracksPressed: public InlineCommand
	{
	public:
		explicit AddTracksPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()) : InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new AddTracksPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class ReturnToPLists: public InlineCommand {
	public:
		explicit ReturnToPLists(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new ReturnToPLists(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};



	class TrackPressed: public InlineCommand
	{
	public:
		explicit TrackPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()) : InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new TrackPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RenameTrackPressed: public InlineCommand
	{
	public:
		explicit RenameTrackPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RenameTrackPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RemoveTrackPressed: public InlineCommand {
	public:
		explicit RemoveTrackPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RemoveTrackPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class UploadTrackPressed: public InlineCommand {
	public:
		explicit UploadTrackPressed(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()) : InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new UploadTrackPressed(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class ReturnToPList: public InlineCommand {
	public:
		explicit ReturnToPList(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new ReturnToPList(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};



	class RemovePListPressed_YN: public InlineCommand
	{
	public:
		explicit RemovePListPressed_YN(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RemovePListPressed_YN(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class RemoveTrackPressed_YN: public InlineCommand {
	public:
		explicit RemoveTrackPressed_YN(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr()): InlineCommand(name, message) {}
		Command* clone() const noexcept override { return new RemoveTrackPressed_YN(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}
