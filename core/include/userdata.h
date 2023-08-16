#pragma once
#include <vector>
#include <string>


namespace mb::core
{
	std::vector<std::string> getUserPlaylists(const int64_t &user_id);
	std::vector<std::string> getUserTracks(const int64_t &user_id, const std::string &playlist_name);

	void createPlaylist(const int64_t &user_id, const std::string &name);
}