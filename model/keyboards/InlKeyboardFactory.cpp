#include "InlKeyboardFactory.h"


namespace board
{
	InlKeyboardFactory::InlKeyboardFactory(int64_t id) :
		user_id(id)
	{
	}
	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::PlayLists() {
		TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
		TgBot::InlineKeyboardButton::Ptr button_x(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr button_y(new TgBot::InlineKeyboardButton);
		TgBot::InlineKeyboardButton::Ptr button_z(new TgBot::InlineKeyboardButton);
		button_x->text = "Y";
		button_y->text = "N";
		button_z->text = "?";
		button_x->callbackData = "1";
		button_y->callbackData = "2";
		button_z->callbackData = "3";
		keyboard->inlineKeyboard = { { button_x, button_y }, { button_z } };

		return keyboard;
	}
	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::TrackMenu(const std::string &track_name) {
		/// create keyboard with concreate track in PlayList
		return nullptr;
	}
	TgBot::InlineKeyboardMarkup::Ptr InlKeyboardFactory::Tracks(const std::string &play_list_name) {
		/// create keyboard with all tracks in PlayList
		return nullptr;
	}
}