#pragma once
#include "Command.h"

namespace cmd::mcr
{
	class Start: public MacroCommand
	{
	public:
		Start () = delete;                                                                                                                     ///
		~Start() = default;                                                                                                                    /// DEFAULT HEAD
		explicit Start (const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): MacroCommand(name, message) {}   ///
		Command* clone() const noexcept override { return new Start(*this); }                                                                  ///

		bool execute(TgBot::Bot &bot) const override;                                                                                          /// EXECUTE METHOD 
	};

	class Info: public MacroCommand
	{
	public:
		Info () = delete;
		~Info() = default;
		explicit Info (const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): MacroCommand(name, message) {}
		Command* clone() const noexcept override { return new Info(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class ShowPlayList: public MacroCommand
	{
	public:
		ShowPlayList () = delete;
		~ShowPlayList() = default;
		ShowPlayList (const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): MacroCommand(name, message) {}
		Command* clone() const noexcept override { return new ShowPlayList(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class CreatePlayList: public MacroCommand
	{
	public:
		CreatePlayList () = delete;
		~CreatePlayList() = default;
		explicit CreatePlayList (const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): MacroCommand(name, message) {}
		Command* clone() const noexcept override { return new CreatePlayList(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}