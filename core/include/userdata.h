#pragma once
#include <tgbot/tgbot.h>



namespace mb::core
{
	std::vector<std::string> getPlayLists(const int64_t &user_id);
	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &plist);


	std::string replace(const std::string &locpth, const std::string &fname);
	void create(const int64_t &user_id, const std::string &locpth);
	void remove(const int64_t &user_id, const std::string &locpth);
	void rename(const int64_t &user_id, const std::string &oldlocpth, const std::string &newlocpth);


	size_t countPLists(const int64_t &user_id);
	size_t countTracks(const int64_t &user_id, const std::string &plist);


	// Locked/unlocked playlist to anything changes
	void lock(const int64_t &id, const std::string &plist, bool lock = true);

	// Return lock-state: true - playlist is blocked
	bool checkLock(const int64_t &id, const std::string &plist);

	// Lock/unlock playlist reffering to response from server
	void lockToResponse(const std::string &response, const int64_t &id, const std::string &plist);

	// Unlock all playlists to start/restart bot
	void changeData();

	// Shell cath 'BotErrors' (old previos buttons click in chat) and notify user, that data is old. Return good/fail click
	bool protectedShell(const int64_t &id, TgBot::Bot &bot, const std::function<void()> &func);

	// Call in protectedShell to throw 'BotException' if data is old
	void pathStressTest(const std::string &path) noexcept(false);
}