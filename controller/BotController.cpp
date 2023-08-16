#include "BotController.h"
#include "AnyCommands.h"
#include "constants.h"
#include "parsers.h"
#include <unordered_map>


namespace mb
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
		static std::unordered_map<std::string, cmd::Command*> inlcmds;
		static std::unordered_map<int64_t, std::string> prev_commands;


		for (const auto &cmd: commands) {
			const auto &type = cmd->type();
			std::shared_ptr<cmd::Command> clone(cmd->clone());

			/// Use clone from command base and set needed argument!
			if (type == CMD_TYPE_MACRO) {
				bot.getEvents().onCommand(cmd->name(), [&, clone](TgBot::Message::Ptr &message) {          
					clone->setMessage(message);
					clone->execute(bot);
					prev_commands[message->chat->id] = core::makeCallback(clone->type(), clone->name());    // save command 
				});
			}
			/// Writing inl. command base
			else if (type == CMD_TYPE_INLINE) {                                                            
				inlcmds[core::prefixCmd(clone->name())] = cmd;
			}
		}

		/// Find neaded inl. command and execute!
		bot.getEvents().onCallbackQuery([&](TgBot::CallbackQuery::Ptr &query) {                            
			const auto &inl = inlcmds.find(core::prefixCmd(query->data));

			if (inl != inlcmds.end()) {
				std::unique_ptr<cmd::Command> wrap(inl->second->clone());
				wrap->setCallbackQuery(query);
				wrap->execute(bot);
			}
			prev_commands[query->message->chat->id] = query->data;
		});

		/// Validator of user input/response with delegate previos bot`s message state (was a fail input)
		bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr &message) {                                    
			auto handler = cmd::any::getHandler(message, prev_commands);

			if (handler) {
				handler->setMessage(message);
				bool res = handler->execute(bot);

				if (res) {
					prev_commands[message->chat->id] = core::makeCallback(NONE, NONE);
				}
			}
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
