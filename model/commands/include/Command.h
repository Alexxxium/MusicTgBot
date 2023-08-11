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

		
		virtual void        log             () const noexcept                        = 0;
		virtual std::string type            () const noexcept                        = 0;
		virtual std::string name            () const noexcept                        = 0;
		virtual Command*    clone           () const noexcept                        = 0;
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


		virtual void        log ()  const noexcept final;
		virtual std::string type()  const noexcept final;
		virtual std::string name()  const noexcept final;
		virtual Command*    clone() const noexcept override;
		virtual bool        execute(TgBot::Bot &bot) const override;                         /// <- BAN


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


		virtual void        log ()  const noexcept final;
		virtual std::string type()  const noexcept final;
		virtual std::string name()  const noexcept final;
		virtual Command*    clone() const noexcept override;
		virtual bool        execute(TgBot::Bot &bot) const override;                         /// <- BAN


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


		virtual void        log ()  const noexcept final;
		virtual std::string type()  const noexcept final;
		virtual std::string name()  const noexcept final;
		virtual Command*    clone() const noexcept override;
		virtual bool        execute(TgBot::Bot &bot) const override;                                /// <- BAN


		virtual void setMessage(const TgBot::Message::Ptr &message)           final; 
		virtual void setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) final;                /// <- BAN


		virtual ~AnyCommand() = default;
		explicit AnyCommand(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr());
	};
}