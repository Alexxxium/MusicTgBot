#pragma once
#include <string>
#include <tgbot/tgbot.h>


namespace mb::core
{
	struct SerializeMessage
	{
	public:
		int64_t id;
		std::string text;
	};

	std::string prefixCmd(const std::string &cmd_name);
	std::string suffixCmd(const std::string &cmd_name);
	std::string parseHTML(const std::string &path);

	std::string prevBotMessage(const int64_t &chat_id);
	void updatePrevBotMessage(const int64_t &chat_id, const std::string &text = "");

	std::string makeCallback(const std::string &prefix, const std::string &suffix);
	std::string makeCallback(const int &prefix, const std::string &suffix);
	std::string makeCallback(const std::string &prefix, const int &suffix);
	std::string makeCallback(const int &prefix, const int &suffix);
}