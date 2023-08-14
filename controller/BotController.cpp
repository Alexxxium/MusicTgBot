#include "BotController.h"
#include "constants.h"
#include "parsers.h"
#include <unordered_map>


namespace ctrl
{
	BotController* BotController::singleton = nullptr;

	BotController::BotController(const std::string &TOKEN) :
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

	void BotController::initCommands(const std::vector<cmd::Command*>& commands)
	{
		std::unordered_map<std::string, cmd::Command*> inl_cmds;

		for (const auto &cmd : commands) {

			const auto type = cmd->type();
			std::shared_ptr<cmd::Command> clone(cmd->clone());

			if (type == cmd::MACRO) {
				bot.getEvents().onCommand(cmd->name(), [&, clone](TgBot::Message::Ptr message) {          /// use clone from command base and set needed argument!
					clone->setMessage(message);
					clone->execute(bot);
					});
			}
			else if (type == cmd::INLINE) {                                                         /// remembering inl. command!
				inl_cmds.insert({ core::prefixCmd(clone->name()), cmd });
			}
			else if (type == cmd::ANY) {

			}
		}

		bot.getEvents().onCallbackQuery([&, inl_cmds](TgBot::CallbackQuery::Ptr query) {                  /// find neaded inl. command and execute!
			const auto &inl = inl_cmds.find(core::prefixCmd(query->data));
			if (inl != inl_cmds.end()) {
				std::unique_ptr<cmd::Command> wrap(inl->second->clone());
				wrap->setCallbackQuery(query);
				wrap->execute(bot);
			}
		});
		bot.getEvents().onAnyMessage([](TgBot::Message::Ptr message) {

		});
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