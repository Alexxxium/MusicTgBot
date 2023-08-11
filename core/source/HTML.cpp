#include "HTML.h"
#include "constants.h"
#include <fstream>

namespace core
{
	std::string parseHTML(const std::string &path)
	{
		std::ifstream file(path);
		if (!file.is_open()) {
			throw err::CANT_OPEN_HTML;
		}
		return std::move(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));
	}
}

