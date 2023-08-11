#include "BotController.h"
#include "constants.h"
//#include "MacroCommands.h"

namespace ctrl
{
	BotController* BotController::singleton = nullptr;

	BotController::BotController(const std::string &TOKEN):
		bot(TOKEN)
	{
	}

	BotController* BotController::getInstanse(const std::string &TOKEN)
	{
		if (!singleton) {
			singleton = new BotController(TOKEN);
		}
		return singleton;
	}

	void BotController::initCommands(const std::vector<cmd::Command*>& cmds)
	{
		for (auto &cmd: cmds) {
			const auto type = cmd->type();

			if (type == cmd::type::MACRO) {
				bot.getEvents().onCommand(cmd->name(), [&, cmd](TgBot::Message::Ptr message) {          /// copy the command from command base and set needed argument!
					cmd->setMessage(message);
					cmd->execute(bot);
				});
			}
			else if (type == cmd::type::INLINE) {
				bot.getEvents().onCallbackQuery([&, cmd](TgBot::CallbackQuery::Ptr query) {
					cmd->setCallbackQuery(query);
					cmd->execute(bot);
				});
			}
			else if (type == cmd::type::ANY) {
				bot.getEvents().onAnyMessage([&, cmd](TgBot::Message::Ptr message) {
					cmd->setMessage(message);
					cmd->execute(bot);
				});
			}
		}
		std::cout << "Bot initialized!" << std::endl;
	}

	void BotController::listen()
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