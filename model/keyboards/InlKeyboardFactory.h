#pragma once
#include <tgbot/tgbot.h>
#include "constants.h"


namespace mb::cmd
{
/// Dinamic factory of inline-keyboards
	class InlKeyboardFactory
	{
	public:
		static TgBot::InlineKeyboardMarkup::Ptr PlayListsMenu(const int64_t &user_id);
		static TgBot::InlineKeyboardMarkup::Ptr PlayListMenu (const int64_t &user_id, const std::string &playlist_name);
		static TgBot::InlineKeyboardMarkup::Ptr TrackMenu(const int64_t &user_id, const std::string &track_local_path);
		static TgBot::InlineKeyboardMarkup::Ptr SelectMenu_YN(types inlcmd, const std::string &yes_callbackdata);
	};
}
