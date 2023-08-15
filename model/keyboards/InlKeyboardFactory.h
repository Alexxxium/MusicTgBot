#pragma once
#include <tgbot/tgbot.h>


namespace mb::cmd
{
	class InlKeyboardFactory
	{
	public:
		static TgBot::InlineKeyboardMarkup::Ptr PlayLists(const int64_t &user_id);
		static TgBot::InlineKeyboardMarkup::Ptr TrackMenu(const int64_t &user_id, const std::string &track_name);
		static TgBot::InlineKeyboardMarkup::Ptr Tracks   (const int64_t &user_id, const std::string &playlist_name);
	};
}
