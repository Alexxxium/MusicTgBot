#include "InlKeyboardFactory.h"


namespace cmd
{
	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::PlayLists(int64_t user_id) {
		TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
		TgBot::InlineKeyboardButton::Ptr button_x(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr button_y(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr button_z(new TgBot::InlineKeyboardButton);
		button_x->text = "Y";
		button_y->text = "N";
		button_z->text = "?";
		button_x->callbackData = "1 3";
		button_y->callbackData = "2 2";
		button_z->callbackData = "3 1";
		keyboard->inlineKeyboard = { { button_x, button_y }, { button_z } };

		return keyboard;
	}
	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::TrackMenu(int64_t user_id, const std::string &track_name) {
		/// create keyboard with concreate track in PlayList
		return nullptr;
	}
	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::Tracks(int64_t user_id, const std::string &play_list_name) {
		/// create keyboard with all tracks in PlayList
		return nullptr;
	}
}