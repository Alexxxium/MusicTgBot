#pragma once
#include "Command.h"
#include <tgbot/tgbot.h>


namespace mb
{
	class BotController
	{
	private:
		TgBot::Bot bot;
		static BotController *singleton;

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
