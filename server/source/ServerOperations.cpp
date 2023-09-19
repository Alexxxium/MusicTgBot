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
			start_id = 1,
			start_args = 2,
			notation_size = 3;

		if (args.size() < notation_size) {
			throw err::INVALID_NOTATION;
		}

		int64_t id = std::stoll(args[start_id]);
		const std::string &target_dir = pth::USER_DATA_DIR + args[start_id] + sl;

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
			start_id = 1,
			start_args = 2,
			notation_size = 3;

		if (args.size() < notation_size) {
			throw err::INVALID_NOTATION;
		}

		int64_t id = std::stoll(args[start_id]);

		for (int i = start_args; i < args.size(); ++i) {
			const auto &tracks = getPlayList(id, args[i]);
			const std::string &target_dir = pth::USER_DATA_DIR + args[start_id] + sl + args[i] + sl;

			for (const auto &track: tracks) {
				auto &audio = TgBot::InputFile::fromFile(target_dir + track, "");
				{
					std::lock_guard<std::mutex> lock(mutex);
					BOT.getApi().sendAudio(id, audio);
				}
			}
		}
	}


	void DownloadAudioGroup::execute(const std::vector<std::string> &args) const {
		constexpr auto sl = "/";
		constexpr int
			start_id = 1,
			start_name = 2,
			start_args = 3,
			notation_size = 4;

		if (args.size() < notation_size) {
			throw err::INVALID_NOTATION;
		}

		std::string path = pth::USER_DATA_DIR + args[start_id] + sl + args[start_name] + sl;
		std::string track;

		for (int i = start_args; i < args.size(); ++i) {
			if (i % 2 == 0) {
				std::string bytes;
				{
					std::lock_guard<std::mutex> lock(mutex);
					bytes = std::move(BOT.getApi().downloadFile(args[i]));
				}

				std::ofstream file(path + track, std::ios::binary);
				if (file.is_open()) {
					file << bytes;
				}
			}
			else {
				track = args[i];
			}
		}

		std::lock_guard<std::mutex> lock(mutex);
		BOT.getApi().sendMessage(std::stoll(args[start_id]), "OK");
	}
}
