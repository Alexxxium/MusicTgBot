#pragma once
#include "Command.h"
//#include <tgbot/tgbot.h>


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
	bool isValidName(const std::string  &file_or_dir);
	bool isValidName(const std::wstring &file_or_dir);

	bool inCmdlet(const std::string &cmd_name);

	template<typename T>
	bool executeCommand(cmd::Command *cmd, const T &setdata, TgBot::Bot &bot) {
		
		if (!cmd) {
			throw err::NULL_CMD_PTR;
		}

		std::unique_ptr<cmd::Command> wrap(nullptr);

		switch (cmd->type())
		{
		case CMD_TYPE_MACRO: case CMD_TYPE_ANY: 
			wrap->setMessage(setdata);
			break;
		case CMD_TYPE_INLINE:
			wrap->setCallbackQuery(setdata);
			break;
		default:
			throw err::UNKNOWN_CMD;
		}

		return wrap->execute(bot);
	}
}