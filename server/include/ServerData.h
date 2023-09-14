#pragma once
#include <vector>
#include <string>



namespace srv 
{
	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &plist);
}