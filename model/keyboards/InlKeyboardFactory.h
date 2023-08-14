#pragma once
#include <tgbot/tgbot.h>

namespace cmd
{
	class InlKeyboardFactory
	{
	public:
		static TgBot::InlineKeyboardMarkup::Ptr PlayLists(int64_t user_id);
		static TgBot::InlineKeyboardMarkup::Ptr TrackMenu(int64_t user_id, const std::string &track_name);
		static TgBot::InlineKeyboardMarkup::Ptr Tracks   (int64_t user_id, const std::string &playlist_name);
	};
}