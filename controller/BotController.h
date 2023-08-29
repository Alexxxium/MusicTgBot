#pragma once
#include "Command.h"



namespace mb
{
/// Class to controll bot
	class BotController
	{
	private:
		TgBot::Bot bot;
		static BotController *singleton;

		static std::unordered_map<std::string, cmd::Command*> inlcmds;
		static std::unordered_map<int64_t, std::string> prev_commands;

		BotController(const std::string &TOKEN);

	public:
		BotController() = delete;
		~BotController() = delete;
		BotController(BotController&&) = delete;
		BotController(const BotController&) = delete;
		BotController& operator=(BotController&&) = delete;
		BotController& operator=(const BotController) = delete;

		static BotController* getInstanse(const std::string &TOKEN) noexcept;


		// Return last good executed command: str("type" "Callback_type data")
		static std::string bufferEntry(const int64_t &id);

		// Iterate array and assign handlers (command shell of execute method)
		void initCommands(const std::vector<cmd::Command*> &cmds);

		// Start bot after initialization
		void listen() noexcept;

		// Get needed command reffering to previos bot message (good executed command) 
		// WARNING: This method can return NULL!
		static cmd::Command* getHandler(TgBot::Message::Ptr &message);
	};
}
