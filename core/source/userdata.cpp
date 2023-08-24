#include "userdata.h"
#include "constants.h"
#include <filesystem>


namespace mb::core
{
	namespace fs = std::filesystem;

	std::vector<std::string> getPlayLists(const int64_t &user_id)
	{
		std::vector<std::string> res;
		std::string target_dir = mb::pth::USER_DATA_DIR + std::to_string(user_id) + '/';

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

	void createPlaylist(const int64_t &user_id, const std::string &name) 
	{
		fs::create_directory(pth::USER_DATA_DIR + std::to_string(user_id) + "/" + name);
	}

	void renamePlayList(const int64_t &user_id, const std::string &old_name, const std::string &new_name) 
	{
		constexpr auto sl = "/";
		std::string pthold = pth::USER_DATA_DIR + std::to_string(user_id) + sl + old_name;
		std::string pthnew = pth::USER_DATA_DIR + std::to_string(user_id) + sl + new_name;
		
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
}
