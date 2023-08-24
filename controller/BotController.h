#pragma once
#include "Command.h"



namespace mb
{
	class BotController
	{
	private:
		TgBot::Bot bot;
		static BotController *singleton;

		std::unordered_map<std::string, cmd::Command*> inlcmds;
		std::unordered_map<int64_t, std::string> prev_commands;

		BotController(const std::string &TOKEN);

	public:
		BotController() = delete;
		~BotController() = delete;
		BotController(BotController&&) = delete;
		BotController(const BotController&) = delete;
		BotController& operator=(BotController&&) = delete;
		BotController& operator=(const BotController) = delete;

		static BotController* getInstanse(const std::string &TOKEN) noexcept;

		void initCommands(const std::vector<cmd::Command*> &cmds);
		void listen() noexcept;
	};
}
