#include "ServerData.h"
#include "ServerConstants.h"
#include <filesystem>


namespace fs = std::filesystem;

namespace srv 
{
	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &plist) {
		constexpr auto sl = "/";

		std::string target_dir = pth::USER_DATA_DIR + std::to_string(user_id) + sl + plist + sl;
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

	std::vector<std::string> split(std::string &&parsestr, const std::string &sep) {
		size_t pos = 0;
		std::vector<std::string> res;

		while ((pos = parsestr.find(sep)) != std::string::npos) {
			res.push_back(parsestr.substr(0, pos));
			parsestr.erase(0, pos + sep.length());
		}
		res.push_back(parsestr);

		return res;
	}
}