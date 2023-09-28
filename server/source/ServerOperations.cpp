#include "ServerOperations.h"
#include "ServerConstants.h"
#include "ServerData.h"
#include "TaskQueue.h"
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
					response += (std::string) sep + s_ + track + _s;
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
						response += (std::string) sep + track;
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


	std::atomic<bool> g_flag;
	std::string tryDownload(const std::string &savepath, const std::string &url) {
		constexpr char wr = '"', sp = ' ', pt = '.';
		constexpr auto cd = "cd", and = " && ", kill = "taskkill /IM yt-dlp.exe /F";

		constexpr time_t timeout = 10'000, pause = 1'000;
		constexpr size_t maxlen  = (size_t) 50 * 1024 * 1024;

		static const std::string cdto = (std::string) cd + sp + (wr + fs::path(pth::DOWNLOAD_SCRIPT).parent_path().string() + wr);
		static const std::string script = fs::path(pth::DOWNLOAD_SCRIPT).filename().string();
		static const std::string closestr = (std::string) cdto + and + kill;
		static const std::vector<std::string> extlist = { "flac", "mp3" };
		static algs::TaskQueue queue;


		for (const auto &ext: extlist) {
			queue.run();
			g_flag.store(true);
			std::string output = (std::string) savepath + pt + ext;
			std::string exestr = (std::string) cdto + and + (script) + sp + (wr + output + wr) + sp + (ext) + sp + (wr + url + wr);
			queue.addTask([&]() {                                                                                                          // thread to executing
				system(exestr.c_str()); 
				g_flag.store(false); 
			});

			time_t count = timeout;
			while (g_flag.load() && count > 0) {                                                                                           // time to execute (controll in main thread)
				std::this_thread::sleep_for(std::chrono::milliseconds(pause));
				count -= pause;
			}
			if (g_flag.load()) {
				system(closestr.c_str());                                                                                                  // broke problems
				continue;
			}

			std::ifstream file(output, std::ios::binary | std::ios::ate);
			if (!fs::exists(output) || !file.is_open()) {                                                                                  // origin file is big
				continue;
			}

			file.seekg(0, std::ios::end);
			if (file.tellg() > maxlen) {                                                                                                   // file size more then 50Mb
				file.close();
				fs::remove(output);
				continue;
			}
			else {
				return pt + ext;                                                                                                           // exstension of download audio
			}
		}
		return "";
	}

	void SendAudioFromURL::execute(const std::vector<std::string> &args) const {
		constexpr auto sl = "/", filestem = "default", s_ = "<s><i>", _s = "</i></s>", sep = "\n";
		std::string report = u8"<i><b>Отчет:</b></i>";
		constexpr int
			start_id = 1,
			start_args = 2,
			notation_size = 3;
		
		if (args.size() < notation_size) {
			throw err::INVALID_NOTATION;
		}

		std::vector<std::string> errorurls;
		int64_t id = std::stoll(args[start_id]);
		std::string savepath = pth::BUFFER_DIR + args[start_id] + sl + filestem;

		for (int i = start_args; i < args.size(); ++i) {
			std::string ext = tryDownload(savepath, args[i]);

			if (ext.empty()) {
				errorurls.push_back(s_ + args[i] + _s);
				continue;
			}

			std::string audiopath = savepath + ext;
			const auto &file = TgBot::InputFile::fromFile(audiopath, "");

			std::lock_guard<std::mutex> lock(mutex);
			BOT.getApi().sendAudio(id, file);
			fs::remove(audiopath);
		}

		if (errorurls.empty()) {
			unlock(args[start_id], "");
			return;
		}
		for (const auto &url: errorurls) {
			report += sep + url;
		}
		std::lock_guard<std::mutex> lock(mutex);
		BOT.getApi().sendMessage(id, report, false, 0, nullptr, "html");
		unlock(args[start_id], "");
	}
}
