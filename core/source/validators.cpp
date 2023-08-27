#include "validators.h"
#include "constants.h"
#include <filesystem>
#include <cstdarg>
#include <codecvt>
#include <fstream>
#include <regex>


namespace mb::core
{
	namespace fs = std::filesystem;

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

	std::string parseHTML(const std::string &path)
	{
		std::ifstream file(path);

		if (!file.is_open()) {
			throw mb::err::CANT_OPEN_HTML_FILE;
		}

		return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
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

	bool exists(const int64_t &id, const std::string &local_path) {
		return fs::exists(core::makePath(id, local_path));
	}

	bool isValidName(const std::string &file_or_dir) {
		return isValidName(strUTF16(file_or_dir));
	}

	bool isValidName(const std::wstring &file_or_dir) {
		constexpr auto regexstr = L"^[a-zA-Z0-9_.\ �-��-�]+$";
		std::wregex valid(regexstr);
		return std::regex_search(file_or_dir, valid);
	}

	// O(N) max N = 7 to 10 <- not problem
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
}