#pragma once
#include <tgbot/tgbot.h>



namespace mb::cmd
{   
/// VIRTUAL BASE: Set message or callback query. Release logic in execute method
	class Command
	{
	protected:
		int _type;
		std::string _name;

	public:
		virtual ~Command() = default;

		// Print Command data in console
		virtual void log() const noexcept = 0;

		// Return intanger type of Command
		virtual int type() const noexcept = 0;

		// Return Command name ("some_type callback_data")
		virtual std::string name() const noexcept = 0;

		// Return silly pointer. WARNING: This method can returned NULL!
		virtual Command* clone() const noexcept = 0;

		// Contain basic logic and return bool value: true - flag to save command data in buffer, false - ignore saving
		virtual bool execute (TgBot::Bot &bot) const = 0;

		// Set message in Command. WARNING: This method banned in Inline Commands!
		virtual void setMessage (const TgBot::Message::Ptr &message) = 0;

		// Set callback query in Command. WARNING: This method banned in not Inline Commands!
		virtual void        setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) = 0;
	};


/// COMMAND PARENTS:
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


	/// EXECUTER OF COMMANDS:
	template <class T>
	struct Execute
	{
	public:
		static bool execute(const std::string &cmdname, TgBot::Message::Ptr message, TgBot::Bot &bot, const std::string &callback = "") {
			std::unique_ptr<Command> wrap(new T(cmdname));

			switch (wrap->type())
			{
			case CMD_TYPE_MACRO: case CMD_TYPE_ANY: {
				wrap->setMessage(message);
				break;
			}
			case CMD_TYPE_INLINE: {
				TgBot::CallbackQuery::Ptr query(new TgBot::CallbackQuery);
				query->message = message;
				query->data = callback;
				wrap->setCallbackQuery(query);
				break;
			}
			default:
				throw err::UNKNOWN_CMD;
				break;
			}

			return wrap->execute(bot);
		}
	};
}
