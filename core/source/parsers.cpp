#include "parsers.h"
#include "constants.h"
#include <fstream>

namespace core
{
	std::string prefixCmd(const std::string &cmd_name) {
		std::stringstream stream(cmd_name);
		std::string res;
		stream >> res;
		return std::move(res);
	}

	std::string suffixCmd(const std::string &cmd_name) {
		std::stringstream stream(cmd_name);
		std::string res;
		stream >> res >> res;
		return std::move(res);
	}

	std::string parseHTML(const std::string &path)
	{
		std::ifstream file(path);
		if (!file.is_open()) {
			throw err::CANT_OPEN_HTML;
		}
		return std::move(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));
	}
}

