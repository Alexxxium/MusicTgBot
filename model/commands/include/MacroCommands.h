#pragma once
#include "Command.h"



namespace mb::cmd::mcr
{
	class Start: public MacroCommand
	{
	public:
		explicit Start (const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()):     /// DEFAULT HEAD:
			MacroCommand(name, message) {}  

		Command* clone() const noexcept override {                                                                 /// CLONE
			return new Start(*this); 
		}

		bool execute(TgBot::Bot &bot) const override;                                                              /// EXECUTE METHOD 
	};

	class Info: public MacroCommand
	{
	public:
		explicit Info (const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): MacroCommand(name, message) {}
		Command* clone() const noexcept override { return new Info(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};

	class ShowPlayLists: public MacroCommand
	{
	public:
		ShowPlayLists (const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr()): MacroCommand(name, message) {}
		Command* clone() const noexcept override { return new ShowPlayLists(*this); }

		bool execute(TgBot::Bot &bot) const override;
	};
}
