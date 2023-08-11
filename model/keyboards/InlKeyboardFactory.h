#pragma once
#include <tgbot/tgbot.h>

namespace board
{
	class InlKeyboardFactory
	{
	private:
		int64_t user_id;

	public:
		InlKeyboardFactory() = delete;
		~InlKeyboardFactory() = default;
		InlKeyboardFactory(InlKeyboardFactory&&) = default;
		InlKeyboardFactory(const InlKeyboardFactory&) = default;
		InlKeyboardFactory& operator=(InlKeyboardFactory&&) = default;
		InlKeyboardFactory& operator=(const InlKeyboardFactory&) = default;

		explicit InlKeyboardFactory(int64_t id);

		TgBot::InlineKeyboardMarkup::Ptr PlayLists();
		TgBot::InlineKeyboardMarkup::Ptr TrackMenu(const std::string &track_name);
		TgBot::InlineKeyboardMarkup::Ptr Tracks(const std::string &play_list_name);
	};
}