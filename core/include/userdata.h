#pragma once
#include <tgbot/tgbot.h>



namespace mb::core
{
	std::vector<std::string> getPlayLists(const int64_t &user_id);
	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &playlist_name);

	void createPlaylist(const int64_t &user_id, const std::string &name);
	void renamePlayList(const int64_t &user_id, const std::string &old_name, const std::string &new_name);
	void removePlayList(const int64_t &user_id, const std::string &name);

	bool protectedShell(const int64_t &id, TgBot::Bot &bot, const std::function<void()> &func);
}