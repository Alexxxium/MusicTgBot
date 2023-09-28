#include "validators.h"
#include "constants.h"
#include <filesystem>
#include <codecvt>
#include <regex>



namespace fs = std::filesystem;

namespace mb::core
{
	std::string parseHTML(const std::string &path) {
		std::ifstream file(path);

		if (!file.is_open()) {
			throw mb::err::CANT_OPEN_HTML_FILE;
		}

		return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	}

	std::string prefixCmd(const std::string &cmd_name) {
		std::stringstream stream(cmd_name);
		std::string res;
		stream >> res;
		return res;
	}

	std::string suffixCmd(const std::string &cmd_name) {
		constexpr char sp = ' ';
		constexpr int sp_i = 0;

		std::stringstream stream(cmd_name);
		std::string res;

		stream >> res;
		std::getline(stream, res);

		if (res.size() > sp_i && res[sp_i] == sp) {
			res.erase(res.begin());
		}
		return res;
	}

	

	std::string makeCallback(const std::string &prefix, const std::string &suffix) {
		return prefix + " " + suffix;
	}

	std::string makeCallback(const int &prefix, const std::string &suffix) {
		return std::to_string(prefix) + " " + suffix;
	}

	std::string makeCallback(const std::string &prefix, const int &suffix) {
		return prefix + " " + std::to_string(suffix);
	}

	std::string makeCallback(const int &prefix, const int &suffix) {
		return std::to_string(prefix) + " " + std::to_string(suffix);
	}



	std::wstring strUTF16(const std::string &utf8str) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(utf8str);
	}

	std::string strUTF8(const std::wstring &utf16str) {
		static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(utf16str);
	}

	bool isValidName(const std::string &file_or_dir) {
		return isValidName(strUTF16(file_or_dir));
	}

	bool isValidName(const std::wstring &file_or_dir) {
		constexpr auto regexstr = L"^[a-zA-Zà-ÿÀ-ÿ¸¨0-9 `~!@#¹$;%^&()_\\[\\]+='-]+$";
		std::wregex valid(regexstr);
		return std::regex_search(file_or_dir, valid);
	}

	bool isURL(const std::string &urlstr) {
		constexpr auto urlprefix = "https://";
		return urlstr.find(urlprefix) == std::string::npos ? false : true;
	}



	// O(N) max N = 10 to 20 <- not problem
	bool inCmdlet(const std::string &cmd_name) {
		constexpr char   sl = '/';
		constexpr size_t sl_i = 0;

		std::string cmd_data;

		if (cmd_name.size() > sl_i && cmd_name[sl_i] == sl) {
			cmd_data = cmd_name.substr(sl_i + 1);
		}	
		else {
			return false;
		}
		for (const auto &cmd: init::CMDLET) {
			if (cmd->name() == cmd_data) {
				return true;
			}
		}
			
		return false;
	}

	bool exists(const int64_t &id, const std::string &locpth) {
		return fs::exists(core::makePath(id, locpth));
	}



	std::string makePath(const std::vector<std::string> &list) {
		std::string res;
		constexpr auto sep = "/";
		auto it = list.begin(), end = list.end(), last = std::prev(end);
		
		for(it; it != end; ++it) {
			res += (it == last) ? *it : *it + sep;
		}
		return res;
	}

	std::string makePath(const int64_t &id, const std::string &local_path) {
		constexpr auto sl = "/";
		return pth::USER_DATA_DIR + std::to_string(id) + sl + local_path;
	}

	std::vector<std::string> splitPath(const std::string &path) {
		constexpr char sep = '/';

		std::string part;
		std::vector<std::string> res;

		for (const auto &i: path) {
			if (i != sep) {
				part += i;
			}
			else {
				res.push_back(part);
				part.clear();
			}
		}

		return res;
	}



	std::string getPList(const uint64_t &id, const std::string &locpth) {
		constexpr auto sl = "/";
		const auto &path = fs::path(pth::USER_DATA_DIR + std::to_string(id) + sl + locpth);

		if (fs::is_directory(path)) {
			return locpth;
		}
		else if (path.has_parent_path()) {
			return path.parent_path().filename().string();
		}
		else {
			throw err::UNCORREKT_PATH;
		}
	}

	std::string getTrack(const uint64_t &id, const std::string &locpth) {
		constexpr auto sl = "/";
		const auto &path = fs::path(pth::USER_DATA_DIR + std::to_string(id) + sl + locpth);

		if (!fs::is_directory(path) && path.has_stem()) {
			return path.stem().string();
		}
		else {
			throw err::UNCORREKT_PATH;
		}
	}

	std::string getExten(const uint64_t &id, const std::string &locpth) {
		constexpr auto sl = "/";
		const auto &path = fs::path(pth::USER_DATA_DIR + std::to_string(id) + sl + locpth);

		if (!fs::is_directory(path) && path.has_extension()) {
			return path.extension().string();
		}
		else {
			throw err::UNCORREKT_PATH;
		}
	}

	std::string makeServerCmd(const std::string &cmd, const std::vector<std::string> &args) {
		constexpr auto  sep = "|";
		std::string res = cmd;

		for (const auto &arg: args) {
			res += sep + arg;
		}
		return res;
	}



	bool isValidPath(const std::string &name, const::std::string &subdir, const int64_t &id, TgBot::Bot &bot) {
		static std::string
			track_large     = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_LARGE_NAME),
			track_little    = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_LITTLE_NAME),
			track_existed   = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_EXISTED_NAME),
			track_uncorrect = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_TRACK + pth::HTML_UNCORRECT_NAME),

			plist_large     = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_LARGE_NAME),
			plist_little    = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_LITTLE_NAME),
			plist_existed   = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_EXISTED_NAME),
			plist_uncorrect = core::parseHTML(pth::MESSAGE_DIR + pth::SUB_DIR_TO_PLIST + pth::HTML_UNCORRECT_NAME);

		constexpr int maxlen = 12, minlen = 3;
		const std::string &path = makePath(id, name);
		const auto &api = bot.getApi();

		std::wstring tgstr = core::strUTF16(name);
		
		if (subdir == pth::SUB_DIR_TO_PLIST) {
			
			if (tgstr.size() < minlen) {
				api.sendMessage(id, plist_little, false, 0, nullptr, mrk::HTML);
				return false;
			}
			else if (tgstr.size() > maxlen) {
				api.sendMessage(id, plist_large, false, 0, nullptr, mrk::HTML);
				return false;
			}
			else if (!isValidName(tgstr)) {
				api.sendMessage(id, plist_uncorrect, false, 0, nullptr, mrk::HTML);
				return false;
			}
			else if (fs::exists(path)) {
				bot.getApi().sendMessage(id, plist_existed, false, 0, nullptr, mrk::HTML);
				return false;
			}
		}
		else if (subdir == pth::SUB_DIR_TO_TRACK) {
			constexpr char bag = ':';
			if (tgstr.find(bag) != std::string::npos) { // BAG: user write symbol ':' and file system interpritate him how local path
				api.sendMessage(id, track_uncorrect, false, 0, nullptr, mrk::HTML);
				return false;
			}
			std::wstring data = fs::path(tgstr).stem().wstring();
			if (data.empty()) {                                                                 
				api.sendMessage(id, track_uncorrect, false, 0, nullptr, mrk::HTML);
				return false;
			}
			else if (data.size() < minlen) {
				api.sendMessage(id, track_little, false, 0, nullptr, mrk::HTML);
				return false;
			}
			else if (data.size() > maxlen) {
				bot.getApi().sendMessage(id, track_large, false, 0, nullptr, mrk::HTML);
				return false;
			}
			else if (!isValidName(data)) { 
				api.sendMessage(id, track_uncorrect, false, 0, nullptr, mrk::HTML);
				return false;
			}
			else if (fs::exists(path)) {
				api.sendMessage(id, track_existed, false, 0, nullptr, mrk::HTML);
				return false;
			}
		}
		else {
			throw err::UNKNOWN_SUBDIR;
		}

		return true;
	}
}