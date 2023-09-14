#include "ServerOperations.h"
#include "ServerConstants.h"
#include "ServerData.h"
#include <tgbot/tgbot.h>


std::mutex mutex;
TgBot::Bot BOT(srv::init::TOKEN);



namespace srv {

	void SendAudio::execute(const std::vector<std::string> &args) const {
		constexpr auto sl = "/";
		constexpr int
			start_name = 0,
			start_args = 1,
			notation_size = 2;

		if (args.size() < notation_size) {
			throw err::INVALID_NOTATION;
		}

		int64_t id = std::stoll(args[start_name]);
		const std::string &target_dir = pth::USER_DATA_DIR + args[start_name] + sl;

		for (int i = start_args; i < args.size(); ++i) {
			const auto &audio = TgBot::InputFile::fromFile(target_dir + args[i], "");
			{
				std::lock_guard<std::mutex> lock(mutex);
				BOT.getApi().sendAudio(id, audio);
			}
		}
	}


	void SendAudioGroup::execute(const std::vector<std::string> &args) const {
		constexpr auto sl = "/";
		constexpr int
			start_name = 0,
			start_args = 1,
			notation_size = 2;

		if (args.size() < notation_size) {
			throw err::INVALID_NOTATION;
		}

		int64_t id = std::stoll(args[start_name]);

		for (int i = start_args; i < args.size(); ++i) {
			const auto &tracks = getPlayList(id, args[i]);
			const std::string &target_dir = pth::USER_DATA_DIR + args[start_name] + sl + args[i] + sl;

			for (const auto &track: tracks) {
				auto &audio = TgBot::InputFile::fromFile(target_dir + track, "");
				{
					std::lock_guard<std::mutex> lock(mutex);
					BOT.getApi().sendAudio(id, audio);
				}
			}
		}
	}
}
