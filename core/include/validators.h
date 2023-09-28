#pragma once
#include "Command.h"



namespace mb::core
{
	std::string parseHTML(const std::string &path);
	std::string prefixCmd(const std::string &cmd_name);
	std::string suffixCmd(const std::string &cmd_name);
	
	std::string makeCallback(const std::string &prefix, const std::string &suffix);
	std::string makeCallback(const int &prefix, const std::string &suffix);
	std::string makeCallback(const std::string &prefix, const int &suffix);
	std::string makeCallback(const int &prefix, const int &suffix);

	
	std::wstring strUTF16(const std::string &utf8str);
	std::string strUTF8(const std::wstring &utf16str);
	bool isValidName(const std::string  &file_or_dir);
	bool isValidName(const std::wstring &file_or_dir);
	bool isURL(const std::string &urlstr);
	

	std::string makePath(const std::vector<std::string> &list);
	std::string makePath(const int64_t &id, const std::string &locpth);
	std::vector<std::string> splitPath(const std::string &path);


	std::string getPList(const uint64_t &id, const std::string &locpth);
	std::string getTrack(const uint64_t &id, const std::string &locpth);
	std::string getExten(const uint64_t &id, const std::string &locpth);
	std::string makeServerCmd(const std::string &cmd, const std::vector<std::string> &args);



	bool inCmdlet(const std::string &cmd_name);

	bool exists(const int64_t &id, const std::string &local_path);

	bool isValidPath(const std::string &name, const::std::string &subdir, const int64_t &message, TgBot::Bot &bot);
}
