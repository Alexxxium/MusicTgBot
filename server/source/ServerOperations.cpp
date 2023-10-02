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

	std::string tryDownload(std::string savepath, const std::string &url, const std::function<void(std::string&)> &update = nullptr) {
		constexpr char wr = '"', sp = ' ', pt = '.', sl = '/';
		constexpr auto cd = "cd", and = " && ";
		constexpr int maxbyites = 50 * 1024 * 1024;

		static std::string script = fs::path(pth::DOWNLOAD_SCRIPT).filename().string();
		static std::vector<std::string> extlist = { "flac", "mp3" };

		for (const auto &ext: extlist) {
			std::string output = savepath + pt + ext;
			if (update != nullptr) {
				std::string track = fs::path(output).filename().string();
				update(track);
				savepath = fs::path(savepath).parent_path().string() + sl + fs::path(track).stem().string();
			}
			std::string syscmd = (script) + sp + (wr + savepath + wr) + sp + (ext) + sp + (wr + url + wr);
			startProcess(syscmd, 20'000, 500);

			output = savepath + pt + ext;
			std::ifstream audio(output, std::ios::binary | std::ios::ate);
			if (!audio.is_open() || !fs::exists(output)) {
				continue;
			}
			audio.seekg(0, std::ios::end);
			if (audio.tellg() > maxbyites) {
				audio.close();
				fs::remove(output);
				continue;
			}
			else {
				return pt + ext;
			}
		}
		return "";
	}

	void DownloadAudioGroup::execute(const std::vector<std::string> &args) const {
		constexpr auto 
			sl = "/", 
			_i = "</i>", 
			_s = "</s>", 
			sep = "\n",
			s_ = "<s>",
			urlcmd = "url",
			dfltname = "default",
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

		std::string track, url;
		std::string response = report;
		std::string path = pth::USER_DATA_DIR + args[start_id] + sl + args[start_name] + sl;
		
		for (int i = start_args; i < args.size(); ++i) {
			if (i % 2 == 0) {
				if (!url.empty()) {
					if (count >= max_tracks) {
						response += (std::string)sep + s_ + args[i] + _s;
					}
					std::string name = dfltname;
					std::string res = tryDownload(path + dfltname, args[i], [&](std::string &track) { 
						update(args[start_id], plist, track); 
					});
					if (res.empty()) {
						response += (std::string) sep + s_ + args[i] + _s;
					}
					else {
						response += (std::string)sep + args[i];
						++count;
					}
					url.clear();
					continue;
				}

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
				args[i] == urlcmd ? url = args[i] : track = args[i];
			}
		}
		std::lock_guard<std::mutex> lock(mutex);
		BOT.getApi().sendMessage(id, response + _i, false, 0, nullptr, "html");
		unlock(args[start_id], args[start_name]);
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
