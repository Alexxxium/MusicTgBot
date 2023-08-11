#pragma once
#include <tgbot/tgbot.h>
#include <Command.h>


namespace ctrl
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

		static BotController* getInstanse(const std::string &TOKEN);

		void initCommands(const std::vector<cmd::Command*> &cmds);
		void listen();
	};
}