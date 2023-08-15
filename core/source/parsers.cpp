#include "parsers.h"
#include "constants.h"
#include <fstream>
#include <filesystem>


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
		std::ostringstream out;
		std::string res, buff;
		stream >> buff;

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

	std::string prevBotMessage(const int64_t &chat_id) {
		return "";
	}


	void updatePrevBotMessage(const int64_t &chat_id, const std::string &text) {

	}
}
