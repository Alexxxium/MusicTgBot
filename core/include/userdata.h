#pragma once
#include <vector>
#include <string>


namespace mb::core
{
	std::vector<std::string> getPlayLists(const int64_t &user_id);
	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &playlist_name);

	void createPlaylist(const int64_t &user_id, const std::string &name);
	void renamePlayList(const int64_t &user_id, const std::string &old_name, const std::string &new_name);
	void removePlayList(const int64_t &user_id, const std::string &name);
}