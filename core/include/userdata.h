#pragma once
#include <tgbot/tgbot.h>



namespace mb::core
{
	std::vector<std::string> getPlayLists(const int64_t &user_id);
	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &playlist_name);

	// Return value: first - track name, second - track extantion
	std::pair<std::string, std::string> getTrack(const int64_t &id, const std::string &local_path);

	void createPlaylist(const int64_t &user_id, const std::string &name);
	void renamePlayList(const int64_t &user_id, const std::string &old_name, const std::string &new_name);
	void removePlayList(const int64_t &user_id, const std::string &name);

	// Shell cath BotErrors (old previos buttons click in chat) and notify user, that data is old. Return good/fail
	bool protectedShell(const int64_t &id, TgBot::Bot &bot, const std::function<void()> &func);

	// Call in protectedShell to throw BotException if data is old
	void pathStressTest(const std::string &path) noexcept(false);
}