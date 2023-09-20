#include "ServerData.h"
#include "ServerConstants.h"
#include <filesystem>
#include <codecvt>
#include <regex>


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

	int countTracks(const int64_t &id, const std::string &plist) {
		constexpr auto sl = "/";

		size_t res = 0;
		std::string target_dir = pth::USER_DATA_DIR + std::to_string(id) + sl + plist + sl;


		if (!fs::exists(target_dir)) {
			throw err::NOT_EXISTED_PLAYLIST;
		}

		for (const auto &entry : fs::directory_iterator(target_dir)) {
			const auto &ext = entry.path().extension().string();
			if (init::SUPEXT.find(ext) != init::SUPEXT.end()) {
				++res;
			}
		}

		return res;
	}

	std::wstring strUTF16(const std::string &utf8str) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(utf8str);
	}

	bool isValidName(const std::string &file_or_dir) {
		return isValidName(strUTF16(file_or_dir));
	}

	bool isValidName(const std::wstring &file_or_dir) {
		constexpr auto regexstr = L"^[a-zA-Zà-ÿÀ-ÿ¸¨0-9 `~!@#¹$;%^&()_\\[\\]+='-]+$";
		std::wregex valid(regexstr);
		return std::regex_search(file_or_dir, valid);
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

	bool hasHash(const std::string &track) {
		constexpr size_t len = 4;
		constexpr char sep = '-', a = 'a', z = 'z';

		std::string stem = fs::path(track).stem().string();
		stem.resize(len);

		if (stem[len - 1] != sep) {
			return false;
		}

		for (int i = 0; i < len - 1; ++i) {
			if (stem[i] < a || stem[i] > z) {
				return false;
			}
		}

		return true;
	}

	std::string hash() {
		constexpr char a = 'a', z = 'z' + 1 - a, sep = '-';
		constexpr int len = 3;

		std::string res;
		time(0);

		for (int i = 0; i < len; ++i) {
			res += a + rand() % z;
		}

		return res + sep;
	}

	void update(const std::string &id, const std::string &plist, std::string &track) {
		constexpr auto standart = "default", sl = "/";
		constexpr int maxlen = 50, hashlen = 4;

		std::string ext = fs::path(track).extension().string();
		std::string stem = fs::path(track).stem().string();
		std::string path = pth::USER_DATA_DIR + id + sl + plist + sl + track;

		if (fs::exists(path)) {
			if (hasHash(track)) {
				std::string hsh = hash();
				for (int i = 0; i < hashlen; ++i) {
					track[i] = hsh[i];
				}
			}
			else {
				track = hash() + track;
			}
			update(id, plist, track);
		}
		else if (!isValidName(stem)) {
			track = standart + ext;
			update(id, plist, track);
		}
		else if (stem.size() > maxlen) {
			stem.resize(maxlen);
			track = stem + ext;
			update(id, plist, track);
		}
	}
}