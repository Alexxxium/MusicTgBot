#include "userdata.h"
#include "constants.h"
#include "validators.h"
#include <filesystem>


namespace mb::core
{
	namespace fs = std::filesystem;

	std::vector<std::string> getPlayLists(const int64_t &user_id)
	{
		constexpr auto sl = "/";

		std::vector<std::string> res;
		std::string target_dir = mb::pth::USER_DATA_DIR + std::to_string(user_id) + sl;

		if (!fs::exists(target_dir)) {
			fs::create_directory(target_dir);
			return {};
		}

		for (const auto &entry: fs::directory_iterator(target_dir)) {
			if (entry.is_directory()) {
				res.push_back(entry.path().filename().string());
			}
		}

		return res;
	}

	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &playlist_name) 
	{
		constexpr auto mp3 = ".mp3", wav = ".wav", flac = ".flac", sl = "/";
		
		std::string target_dir = mb::pth::USER_DATA_DIR + std::to_string(user_id) + sl + playlist_name + sl;
		std::vector<std::string> res;

		if (!fs::exists(target_dir)) {
			throw err::NOT_EXISTED_PLAYLIST;
		}

		for (const auto &entry: fs::directory_iterator(target_dir)) {
			const auto &ext = entry.path().extension().string();
			if (ext == mp3 || ext == wav || ext == flac) {
				res.push_back(entry.path().filename().string());
			}
		}

		return res;
	}

	std::pair<std::string, std::string> getTrack(const int64_t &id, const std::string &local_path)
	{
		const std::string path = core::makePath(id, local_path);

		if (!fs::exists(path)) {
			throw err::NOT_EXISTED_TRACK;
		}

		return { 
			fs::path(path).stem().string(),
			fs::path(path).extension().string()
		};
	}



	void createPlaylist(const int64_t &user_id, const std::string &name) 
	{
		fs::create_directory(pth::USER_DATA_DIR + std::to_string(user_id) + "/" + name);
	}

	void renamePlayList(const int64_t &user_id, const std::string &old_name, const std::string &new_name) 
	{
		constexpr auto sl  = "/";

		std::string pthold = pth::USER_DATA_DIR + std::to_string(user_id) + sl + old_name;
		std::string pthnew = pth::USER_DATA_DIR + std::to_string(user_id) + sl + new_name;

		if (!fs::exists(pthold)) {
			throw err::NOT_EXISTED_PLAYLIST;
		}
		
		fs::rename(pthold, pthnew);
	}

	void removePlayList(const int64_t &user_id, const std::string &name) 
	{
		constexpr auto sl = "/";

		const std::string path = pth::USER_DATA_DIR + std::to_string(user_id) + sl + name;

		if (!fs::exists(path)) {
			throw err::NOT_EXISTED_PLAYLIST;
		}

		fs::remove_all(pth::USER_DATA_DIR + std::to_string(user_id) + sl + name);
	}


	bool protectedShell(const int64_t &id, TgBot::Bot &bot, const std::function<void()> &func)
	{
		static const std::string text = core::parseHTML(pth::MESSAGE_DIR + pth::HTML_OLD_DATA);
		
		try {
			func();
		}
		catch (const DataError &err) {
			bot.getApi().sendMessage(id, text, false, 0, nullptr, mrk::HTML);
			return false;
		}

		return true;
	}

	void pathStressTest(const std::string &path) noexcept(false) {
		if (!fs::exists(path)) {
			throw err::OLD_DATA;
		}
	}
}
