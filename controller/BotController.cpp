#include "BotController.h"
#include "AnyCommands.h"
#include "validators.h"
#include "constants.h"
#include "userdata.h"


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
		for (const auto &cmd: commands) {
			
			const auto &type = cmd->type();
			std::shared_ptr<cmd::Command> clone(cmd->clone());

			/// Use clone from command base and set needed argument!
			if (type == CMD_TYPE_MACRO) {
				bot.getEvents().onCommand(cmd->name(), [&, clone](TgBot::Message::Ptr &message) {          
					clone->setMessage(message);
					if (clone->execute(bot)) {
						prev_commands[message->chat->id] = core::makeCallback(clone->type(), clone->name());    // save command in buffer if need
					}
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
				core::protectedShell(query->message->chat->id, bot, [&]() {                                    // handle not actual buttons clicks
					std::string data = core::suffixCmd(query->data);
					std::string id_str = std::to_string(query->message->chat->id);

					if (data != NONE) {                                                                        // check state in filesystem -> handle exceptions
						core::pathStressTest(core::makePath({ pth::USER_DATA_DIR, id_str, data }));
					}
		
					std::unique_ptr<cmd::Command> wrap(inl->second->clone());
					wrap->setCallbackQuery(query);

					if (wrap->execute(bot)) {
						prev_commands[query->message->chat->id] = query->data;
					}
				});
			}
		});

		/// Validator of user input/response with delegate previos bot`s message state (was a fail input)
		bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr &message) { 
			std::unique_ptr<cmd::Command> handler(cmd::any::getHandler(message, prev_commands));

			if (handler) {
				handler->setMessage(message);
				if (handler->execute(bot)) {
					prev_commands[message->chat->id] = core::makeCallback(NONE, NONE);
				}
			}
		});
	}


	void BotController::listen() noexcept
	{
		constexpr auto
			bot_id       = "Bot id:\t",
			listening    = "Listening...",

			bot_err      = "-b error:\t",
			code_err     = "-c error:\t",
			data_err     = "-d error:\t",
			unknown_err  = "-u error:\t",
			unknown_type = "Unknown type!";


		std::cout << 
			bot_id << bot.getApi().getMe()->id << '\n' << 
			listening << '\n' << std::endl;
	
		try {
			bot.getApi().deleteWebhook();
			TgBot::TgLongPoll longPoll(bot);

			while (true) {
				longPoll.start();
			}
		}
		catch (const BotError &err) {
			std::cout << bot_err << err.what() << std::endl;
		}
		catch (const DataError &err) {
			std::cout << data_err << err.what() << std::endl;
		}
		catch (const std::exception &err) {
			std::cout << code_err << err.what() << std::endl;
		}
		catch (...) {
			std::cout << unknown_err << unknown_type << std::endl;
		}
	}
}
