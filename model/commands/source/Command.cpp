#include "Command.h"
#include "constants.h"

namespace cmd
{
	void AnyCommand::log() const noexcept {
		Command::log();
	}
	void MacroCommand::log() const noexcept {
		Command::log();
	}
	void InlineCommand::log() const noexcept {
		Command::log();
	}

	Command* AnyCommand::clone() const noexcept {
		return new AnyCommand(*this);
	}
	Command* MacroCommand::clone() const noexcept {
		return new MacroCommand(*this);
	}
	Command* InlineCommand::clone() const noexcept {
		return new InlineCommand(*this);
	}

	inline void Command::log() const noexcept {
		std::cout <<
			"-l command log:" << '\n' <<
			"type:  \t" << type() << '\n' <<
			"name:  \t" << name() << '\n' << std::endl;
	}
	inline std::string Command::type() const noexcept {
		return _type;
	}
	inline std::string Command::name() const noexcept {
		return _name;
	}
	
	std::string AnyCommand::type() const noexcept {
		return Command::type();
	}
	std::string AnyCommand::name() const noexcept {
		return Command::name();
	}
	std::string MacroCommand::type() const noexcept {
		return Command::type();
	}
	std::string MacroCommand::name() const noexcept {
		return Command::name();
	}
	std::string InlineCommand::type() const noexcept {
		return Command::type();
	}
	std::string InlineCommand::name() const noexcept {
		return Command::name();
	}

	void AnyCommand::setMessage(const TgBot::Message::Ptr &message) {
		_message = message;
	}
	void MacroCommand::setMessage(const TgBot::Message::Ptr &message) {
		_message = message;
	}
	void InlineCommand::setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) {
		_query = query;
	}


	AnyCommand::AnyCommand(const std::string &name, const TgBot::Message::Ptr &message) {
		_message = message;
		_type = type::ANY;
		_name = name;
	}
	MacroCommand::MacroCommand(const std::string &name, const TgBot::Message::Ptr &message) {
		_message = message;
		_type = type::MACRO;
		_name = name;
	}
	InlineCommand::InlineCommand(const std::string &name, const TgBot::CallbackQuery::Ptr &query) {
		_query = query;
		_type = type::INLINE;
		_name = name;
	}


// Embargo:
	bool AnyCommand::execute(TgBot::Bot &bot) const {
		throw err::EMBARGO;
	}
	bool MacroCommand::execute(TgBot::Bot &bot) const {
		throw err::EMBARGO;
	}
	bool InlineCommand::execute(TgBot::Bot &bot) const {
		throw err::EMBARGO;
	}
	void InlineCommand::setMessage(const TgBot::Message::Ptr &message) {
		throw err::EMBARGO;
	}
	void AnyCommand::setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) {
		throw err::EMBARGO;
	}
	void MacroCommand::setCallbackQuery(const TgBot::CallbackQuery::Ptr &query) {
		throw err::EMBARGO;
	}
}