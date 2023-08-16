#include "parsers.h"
#include "constants.h"
#include <codecvt>
#include <fstream>
#include <filesystem>
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
		std::stringstream stream(cmd_name);
		std::string res;

		stream >> res;
		std::getline(stream, res);

		if (res.size() > 0 && res[0] == ' ') {
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

	bool isValidName(const std::string &file_or_dir) {
		return isValidName(strUTF16(file_or_dir));
	}

	bool isValidName(const std::wstring &file_or_dir) {
		constexpr auto regexstr = L"^[a-zA-Z0-9_\ à-ÿÀ-ÿ¸¨]+$";
		std::wregex valid(regexstr);

		return std::regex_search(file_or_dir, valid);
	}
}
