#include "BotController.h"
#include "constants.h"


namespace ctrl
{
	BotController* BotController::singleton = nullptr;

	BotController::BotController(const std::string &TOKEN):
		bot(TOKEN)
	{
	}

	BotController* BotController::getInstanse(const std::string &TOKEN) noexcept
	{
		if (!singleton) {
			singleton = new BotController(TOKEN);
		}
		return singleton;
	}

	void BotController::initCommands(const std::vector<cmd::Command*>& cmds)
	{
		for (const auto &cmd: cmds) {
			const auto type = cmd->type();
			std::shared_ptr<cmd::Command> clone(cmd->clone());

			if (type == cmd::type::MACRO) {
				bot.getEvents().onCommand(cmd->name(), [&, clone](TgBot::Message::Ptr message) {          /// use clone from command base and set needed argument!
					clone->setMessage(message);
					clone->execute(bot);
				});
			}
			else if (type == cmd::type::INLINE) {
				bot.getEvents().onCallbackQuery([&, clone](TgBot::CallbackQuery::Ptr query) {
					clone->setCallbackQuery(query);
					clone->execute(bot);
				});
			}
			else if (type == cmd::type::ANY) {
				bot.getEvents().onAnyMessage([&, clone](TgBot::Message::Ptr message) {
					clone->setMessage(message);
					clone->execute(bot);
				});
			}
		}
		std::cout << "Bot initialized!" << std::endl;
	}

	void BotController::listen() noexcept
	{
		std::cout << "Listening...\n" << std::endl;

		try {
			bot.getApi().deleteWebhook();
			TgBot::TgLongPoll longPoll(bot);

			while (true) {
				longPoll.start();
			}
		}
		catch (const std::exception &exc) {
			std::cout << "-b Error:\t" << exc.what() << std::endl;
		}
		catch (...) {
			std::cout << "-u Error:\t" << "Unkown type" << std::endl;
		}
	}
}