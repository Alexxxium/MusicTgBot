#include "InlineCommands.h"
#include "MacroCommands.h"
#include "AnyCommands.h"
#include "validators.h"
#include "constants.h"
#include "userdata.h"

#include <filesystem>



namespace mb::cmd::any
{
	namespace fs = std::filesystem;

	Command* getHandler(TgBot::Message::Ptr &message, std::unordered_map<int64_t, std::string> &buffer)
	{
		if (core::inCmdlet(message->text)) {
			return nullptr;
		}

		auto &it = buffer.find(message->chat->id);

		if (it == buffer.end()) {
			return nullptr;
		}
		else if (core::prefixCmd(it->second) == CBQ_ADD_PLAYLIST) {
			return new CreatePlayList(std::to_string(NONE));
		}
		else if (core::prefixCmd(it->second) == CBQ_RENAME_PLAYLIST) {
			return new RenamePlayList(core::suffixCmd(it->second));
		}

		return nullptr;
	}

	bool isValidName(TgBot::Message::Ptr message, TgBot::Bot &bot) {
		constexpr int8_t
			minlen       = 1,
			maxlen       = 60;
		const auto &html = core::parseHTML;
		const auto &text = message->text;
		const auto &id   = message->chat->id;
		std::string path = pth::USER_DATA_DIR + std::to_string(id) + "/" + text;

		if (text.size() > maxlen) {
			bot.getApi().sendMessage(id, html(pth::MESSAGE_DIR + pth::HTML_LARGE_PLIST_NAME), false, 0, nullptr, mrk::HTML);
			return false;
		}
		if (text.size() < minlen) {
			bot.getApi().sendMessage(id, html(pth::MESSAGE_DIR + pth::HTML_LITTLE_PLIST_NAME), false, 0, nullptr, mrk::HTML);
			return false;
		}
		if (!core::isValidName(text)) {
			bot.getApi().sendMessage(id, html(pth::MESSAGE_DIR + pth::HTML_UNCORRECT_PLIST_NAME), false, 0, nullptr, mrk::HTML);
			return false;
		}
		if (fs::exists(path)) {
			bot.getApi().sendMessage(id, html(pth::MESSAGE_DIR + pth::HTML_EXISTED_PLIST_NAME), false, 0, nullptr, mrk::HTML);
			return false;
		}

		return true;
	}



	bool CreatePlayList::execute(TgBot::Bot &bot) const
	{
		if (!isValidName(_message, bot)) {
			return false;
		}
		core::createPlaylist(_message->chat->id, _message->text);

		bot.getApi().sendMessage(_message->chat->id, core::parseHTML(pth::MESSAGE_DIR + pth::HTML_CREATED_PLIST), false, 0, nullptr, mrk::HTML);
		return Execute<mcr::ShowPlayLists>::execute(name(), _message, bot);
	}

	bool RenamePlayList::execute(TgBot::Bot &bot) const {
		if (!isValidName(_message, bot)) {
			return false;
		}
		return core::protectedShell(_message->chat->id, bot, [&]() {
			core::renamePlayList(_message->chat->id, _name, _message->text);
			Execute<inl::PlayListPressed>::execute(_message->text, _message, bot, core::makeCallback(CBQ_SHOW_PLAYLIST, _message->text));
		});
	}
}
