#pragma once
#include "Command.h"



namespace mb::core
{
	std::string prefixCmd(const std::string &cmd_name);
	std::string suffixCmd(const std::string &cmd_name);
	std::string parseHTML(const std::string &path);

	std::string makeCallback(const std::string &prefix, const std::string &suffix);
	std::string makeCallback(const int &prefix, const std::string &suffix);
	std::string makeCallback(const std::string &prefix, const int &suffix);
	std::string makeCallback(const int &prefix, const int &suffix);

	std::wstring strUTF16(const std::string &utf8str);
	bool exists(const int64_t &id, const std::string &local_path);

	bool isValidName(const std::string  &file_or_dir);
	bool isValidName(const std::wstring &file_or_dir);
	
	bool inCmdlet(const std::string &cmd_name);

	std::string makePath(const std::vector<std::string> &list);
	std::string makePath(const int64_t &id, const std::string &local_path);
	std::vector<std::string> splitPath(const std::string &path);
}
