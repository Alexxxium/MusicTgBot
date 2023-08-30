#pragma once
#include <tgbot/tgbot.h>



namespace mb::cmd
{   
/// VIRTUAL BASE: Set message or callback query and describe basic logic in execute method
	class Command
	{
	protected:
		int _type;
		std::string _name;

	public:
		virtual ~Command() = default;

		// Print Command data in console
		virtual void log() const noexcept = 0;

		// Return intager type of Command
		virtual int type() const noexcept = 0;

		// Return Command name ("identify_type" "callback data ... if need")
		virtual std::string name() const noexcept = 0;

		// Return silly pointer to copy
		virtual Command* clone() const noexcept = 0;

		// Contain basic logic and return bool value: true - flag to save command name in buffer, false - ignore saving
		virtual bool execute (TgBot::Bot &bot) const = 0;

		// Set 'Message' in Command. WARNING: This method banned in Inline Commands!
		virtual void setMessage (const TgBot::Message::Ptr &message) = 0;

		// Set 'CallbackQuery' in Command. WARNING: This method banned in not Inline Commands!
		virtual void setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) = 0;
	};


/// MACRO COMMAND PARENT: Describe getters and setters except 'setCallbackQuery'
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
		virtual int         type()  const noexcept final;
		virtual std::string name()  const noexcept final;
		virtual Command*    clone() const noexcept override;
		virtual bool        execute(TgBot::Bot &bot) const override;                         /// <- BAN


		virtual void setMessage      (const TgBot::Message::Ptr &message)     final;
		virtual void setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) final;         /// <- BAN 


		virtual ~MacroCommand() = default;
		explicit MacroCommand(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr());
	};


/// INLINE COMMAND PARENT: Describe getters and setters except 'setMessage'
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
		virtual int         type()  const noexcept final;
		virtual std::string name()  const noexcept final;
		virtual Command*    clone() const noexcept override;
		virtual bool        execute(TgBot::Bot &bot) const override;                         /// <- BAN


		virtual void setMessage      (const TgBot::Message::Ptr &message)     final;         /// <- BAN 
		virtual void setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) final;


		virtual ~InlineCommand() = default;
		explicit InlineCommand(const std::string &name, const TgBot::CallbackQuery::Ptr &message = TgBot::CallbackQuery::Ptr());
	};


/// ANY COMMAND PARENT: Describe getters and setters except 'setCallbackQuery'
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
		virtual int         type()  const noexcept final;
		virtual std::string name()  const noexcept final;
		virtual Command*    clone() const noexcept override;
		virtual bool        execute(TgBot::Bot &bot) const override;                                /// <- BAN


		virtual void setMessage(const TgBot::Message::Ptr &message)           final; 
		virtual void setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) final;                /// <- BAN


		virtual ~AnyCommand() = default;
		explicit AnyCommand(const std::string &name, const TgBot::Message::Ptr &message = TgBot::Message::Ptr());
	};
	

/// EXECUTER OF COMMANDS: Use if need make disposable protected command shell for memory pointer to invoke execute method
	template <class T>
	struct Execute
	{
	public:
		static bool execute(const std::string &cmdname, TgBot::Message::Ptr message, TgBot::Bot &bot, const std::string &callback = "");
		static bool execute(const int &cmdname, TgBot::Message::Ptr message, TgBot::Bot &bot, const std::string &callback = "");
	};
}

#include "Command.inl"
