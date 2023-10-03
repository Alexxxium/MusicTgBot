#include "userdata.h"
#include "constants.h"
#include "validators.h"
#include <filesystem>



namespace fs = std::filesystem;

namespace mb::core
{
	std::vector<std::string> getPlayLists(const int64_t &user_id) {
		constexpr auto sl = "/";

		std::vector<std::string> res;
		std::string target_dir = pth::USER_DATA_DIR + std::to_string(user_id) + sl;

		if (!fs::exists(pth::USER_DATA_DIR)) {
			fs::create_directory(pth::USER_DATA_DIR);
		}
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

	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &plist) {
		constexpr auto sl = "/";
		
		std::string target_dir = mb::pth::USER_DATA_DIR + std::to_string(user_id) + sl + plist + sl;
		std::vector<std::string> res;

		if (!fs::exists(target_dir)) {
			throw err::NOT_EXISTED_PLAYLIST;
		}

		for (const auto &entry: fs::directory_iterator(target_dir)) {
			const auto &ext = entry.path().extension().string();
			if (init::SUPEXT.find(ext) != init::SUPEXT.end()) {
				res.push_back(entry.path().filename().string());
			}
		}

		return res;
	}

	

	std::string replace(const std::string &lclpth, const std::string &fname) {
		std::string ext = fs::path(lclpth).extension().string();
		return fs::path(lclpth).replace_filename(fname + ext).string();
	}

	void create(const int64_t &user_id, const std::string &lclpth) {
		constexpr auto sl = "/";
		fs::path path = fs::path(pth::USER_DATA_DIR + std::to_string(user_id) + sl + lclpth);

		if (path.has_extension()) {
			std::ofstream(path);
		}
		else {
			fs::create_directory(path);
		}
	}

	void remove(const int64_t &user_id, const std::string &lclpth) {
		constexpr auto sl = "/";
		fs::path path = fs::path(pth::USER_DATA_DIR + std::to_string(user_id) + sl + lclpth);

		if (!fs::exists(path)) {
			throw err::OLD_DATA;
		}
		fs::remove_all(path);
	}

	void rename(const int64_t &user_id, const std::string &oldlclpth, const std::string &newlclpth) {
		constexpr auto sl = "/";
		std::string
			root = pth::USER_DATA_DIR + std::to_string(user_id) + sl,
			old_ = root + oldlclpth,
			new_ = root + newlclpth;

		fs::rename(old_, new_);
	}



	size_t countPLists(const int64_t &user_id) {
		constexpr auto sl = "/";

		size_t res = 0;
		std::string target_dir = mb::pth::USER_DATA_DIR + std::to_string(user_id) + sl;

		if (!fs::exists(target_dir)) {
			throw err::NOT_EXISTED_DIR;
		}

		for (const auto &entry: fs::directory_iterator(target_dir)) {
			if (entry.is_directory()) {
				++res;
			}
		}

		return res;
	}

	size_t countTracks(const int64_t &user_id, const std::string &plist) {
		constexpr auto sl = "/";

		size_t res = 0;
		std::string target_dir = mb::pth::USER_DATA_DIR + std::to_string(user_id) + sl + plist + sl;


		if (!fs::exists(target_dir)) {
			throw err::NOT_EXISTED_PLAYLIST;
		}

		for (const auto &entry: fs::directory_iterator(target_dir)) {
			const auto &ext = entry.path().extension().string();
			if (init::SUPEXT.find(ext) != init::SUPEXT.end()) {
				++res;
			}
		}

		return res;
	}


	void lock(const int64_t &id, const std::string &loclpath, bool lock) {
		constexpr auto sl = "/";
		std::string path = loclpath.empty() ? 
			pth::BUFFER_DIR + std::to_string(id) + sl + pth::LOCK_FILE : 
			pth::USER_DATA_DIR + std::to_string(id) + sl + core::getPList(id, loclpath) + sl + pth::LOCK_FILE;

		if (!fs::exists(pth::BUFFER_DIR)) {
			fs::create_directory(pth::BUFFER_DIR);
		}
		if (!fs::exists(pth::USER_DATA_DIR)) {
			fs::create_directory(pth::USER_DATA_DIR);
		}

		if (!fs::exists(path)) {
			std::string parent_dir = fs::path(path).parent_path().string();
			if (!fs::exists(parent_dir)) {
				fs::create_directory(parent_dir);
			}
			std::ofstream file(path);
			if (file.is_open()) {
				file << std::to_string(lock);
				file.close();
			}
			else {
				throw err::CANT_OPEN_LOCK_FILE;
			}
		}
		else {
			std::fstream file(path);
			if (file.is_open()) {
				file.seekg(0, std::ios::beg);
				file << std::to_string(lock);
				file.close();
			}
			else {
				throw err::CANT_OPEN_LOCK_FILE;
			}
		}
	}

	bool checkLock(const int64_t &id, const std::string &loclpath) {
		constexpr auto sl = "/", lockbit = "1";
		std::string path = loclpath.empty() ? 
			pth::BUFFER_DIR + std::to_string(id) + sl + pth::LOCK_FILE :
			pth::USER_DATA_DIR + std::to_string(id) + sl + core::getPList(id, loclpath) + sl + pth::LOCK_FILE;

		if (!fs::exists(path)) {
			lock(id, loclpath, false);
			return false;
		}
		std::fstream file(path);
		if (!file.is_open()) {
			return true;
		}

		std::string buff;
		file >> buff;

		return buff == lockbit ? true : false;
	}

	void lockToResponse(const std::string &response, const int64_t &id, const std::string &plist) {
		constexpr auto good = u8"<i><b>Ответ от сервера: </b>запрос принят и отправлен в очередь!</i>";
		response == good ? lock(id, plist, true) : lock(id, plist, false);
	}

	void changeData() {
		std::vector<int64_t> ids;

		if (!fs::exists(pth::USER_DATA_DIR)) {
			fs::create_directory(pth::USER_DATA_DIR);
		}
		if (!fs::exists(pth::BUFFER_DIR)) {
			fs::create_directory(pth::BUFFER_DIR);
		}
		else {
			fs::remove_all(pth::BUFFER_DIR);
			changeData();
		}

		for (const auto &entry: fs::directory_iterator(pth::USER_DATA_DIR)) {
			if (entry.is_directory()) {
				try {
					ids.push_back(std::stoll(entry.path().stem().string()));
				}
				catch (...) {
					// not int dir name
				}
			}
		}

		for (const auto &id: ids) {
			lock(id, "", false);
			const auto &plists = core::getPlayLists(id);
			for (const auto &plist: plists) {
				lock(id, plist, false);
			}
		}
	}

	bool protectedShell(const int64_t &id, TgBot::Bot &bot, const std::function<void()> &func) {
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
