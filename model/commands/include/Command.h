#pragma once
#include <string>
#include <tgbot/tgbot.h>

namespace cmd
{   
// Virtual base:
	class Command
	{
	protected:
		std::string _type, _name;

	public:
		virtual ~Command() = default;

		virtual std::string type            () const                                 = 0;
		virtual std::string name            () const                                 = 0;
		virtual bool        execute         (TgBot::Bot &bot) const                  = 0;
		virtual void        setMessage      (const TgBot::Message::Ptr &message)     = 0;
		virtual void        setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) = 0;
	};


// Parents:
	class MacroCommand: public Command
	{
	protected:
		TgBot::Message::Ptr _message;

	public:
		MacroCommand() = default;
		MacroCommand(MacroCommand&&) = delete;
		MacroCommand(const MacroCommand&) = default;
		MacroCommand& operator=(MacroCommand&&) = delete;
		MacroCommand& operator=(const MacroCommand&) = default;


		virtual std::string type() const final;
		virtual std::string name() const final;
		virtual bool        execute(TgBot::Bot &bot) const;                                  /// <- BAN


		virtual void setMessage      (const TgBot::Message::Ptr &message)     final;
		virtual void setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) final;         /// <- BAN 


		virtual ~MacroCommand() = default;
		explicit MacroCommand(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr());
	};



	class InlineCommand: public Command
	{
	protected:
		TgBot::CallbackQuery::Ptr _query;

	public:
		InlineCommand() = default;
		InlineCommand(InlineCommand&&) = delete;
		InlineCommand(const InlineCommand&) = default;
		InlineCommand& operator=(InlineCommand&&) = delete;
		InlineCommand& operator=(const InlineCommand&) = default;


		virtual std::string type() const final;
		virtual std::string name() const final;
		virtual bool        execute(TgBot::Bot &bot) const;                                  /// <- BAN


		virtual void setMessage      (const TgBot::Message::Ptr &message)     final;         /// <- BAN 
		virtual void setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) final;


		virtual ~InlineCommand() = default;
		explicit InlineCommand(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr());
	};



	class AnyCommand: public Command
	{
	protected:
		TgBot::Message::Ptr _message;

	public:
		AnyCommand() = default;
		AnyCommand(AnyCommand&&) = delete;
		AnyCommand(const AnyCommand&) = default;
		AnyCommand& operator=(AnyCommand&&) = delete;
		AnyCommand& operator=(const AnyCommand&) = default;


		virtual std::string type() const final;
		virtual std::string name() const final;
		virtual bool        execute(TgBot::Bot &bot) const;                                         /// <- BAN


		virtual void        setMessage(const TgBot::Message::Ptr &message)           final; 
		virtual void        setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) final;         /// <- BAN


		virtual ~AnyCommand() = default;
		explicit AnyCommand(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr());
	};
}