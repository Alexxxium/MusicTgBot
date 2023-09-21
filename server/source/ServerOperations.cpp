#include "ServerOperations.h"
#include "ServerConstants.h"
#include "ServerData.h"
#include <tgbot/tgbot.h>
#include <filesystem>


std::mutex mutex;
TgBot::Bot BOT(srv::init::TOKEN);

namespace fs = std::filesystem;

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
			unlock(args[start_id], args[i]);
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
			unlock(args[start_id], args[i]);
		}
	}


	void DownloadAudioGroup::execute(const std::vector<std::string> &args) const {
		constexpr auto 
			sl = "/", 
			_i = "</i>", 
			_s = "</s>", 
			sep = "\n",
			s_ = "<s>",
			report = u8"<i><b>Отчет:</b>";

		constexpr int
			start_id = 1,
			start_name = 2,
			start_args = 3,
			notation_size = 4,
			max_tracks = 50;

		if (args.size() < notation_size) {
			throw err::INVALID_NOTATION;
		}

		int64_t id = std::stoll(args[start_id]);
		const std::string &plist = args[start_name];
		int count = countTracks(id, plist);

		std::string track;
		std::string response = report;
		std::string path = pth::USER_DATA_DIR + args[start_id] + sl + args[start_name] + sl;
		
		for (int i = start_args; i < args.size(); ++i) {
			if (i % 2 == 0) {
				TgBot::File::Ptr tgfile;
				std::string bytes;

				std::lock_guard<std::mutex> lock(mutex);

				// File is big
				try {
					tgfile = BOT.getApi().getFile(args[i]);
				}
				catch (const std::exception&) {
					response += (std::string)sep + s_ + track + _s;
					continue;
				}
				
				if (count >= max_tracks) {
					response += (std::string) sep + s_ + track + _s;
				}
				else {
					update(args[start_id], plist, track);

					bytes = BOT.getApi().downloadFile(tgfile->filePath);
					std::ofstream file(path + track, std::ios::binary);

					if (file.is_open()) {
						file << bytes;
						file.close();
						response += (std::string)sep + track;
						++count;
					}
					else {
						throw std::runtime_error("Can`t open music file to write!");
					}
				}
			}
			else {
				track = args[i];
			}
		}
		std::lock_guard<std::mutex> lock(mutex);
		BOT.getApi().sendMessage(id, response + _i, false, 0, nullptr, "html");
		unlock(args[start_id], args[start_name]);
	}
}
