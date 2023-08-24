#include "AnyCommands.h"
#include "MacroCommands.h"
#include "InlineCommands.h"
#include "constants.h"
#include "userdata.h"
#include "parsers.h"
#include <filesystem>
#include <regex>


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
		else if (core::prefixCmd(it->second) == std::to_string(CBQ_ADD_PLAYLIST)) {
			return new CreatePlayList(std::to_string(NONE));
		}
		else if (core::prefixCmd(it->second) == std::to_string(CBQ_RENAME_PLAYLIST)) {
			return new RenamePlayList(core::suffixCmd(it->second));
		}

		return nullptr;
	}

	bool isValidName(TgBot::Message::Ptr message, TgBot::Bot &bot) {
		constexpr int8_t
			minlen       = 1,
			maxlen       = 25;
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
		log();

		if (!isValidName(_message, bot)) {
			return false;
		}

		core::createPlaylist(_message->chat->id, _message->text);

		bot.getApi().sendMessage(_message->chat->id, core::parseHTML(pth::MESSAGE_DIR + pth::HTML_CREATED_PLIST), false, 0, nullptr, mrk::HTML);

		std::unique_ptr<Command> plist(new mcr::ShowPlayLists(name()));
		plist->setMessage(_message);
		plist->execute(bot);

		return true;
	}

	bool RenamePlayList::execute(TgBot::Bot &bot) const {
		log();
		
		if (!isValidName(_message, bot)) {
			return false;
		}

		core::renamePlayList(_message->chat->id, name(), _message->text);

		std::unique_ptr<Command>  plist(new inl::PlayListPressed(_message->text));
		TgBot::CallbackQuery::Ptr cback(new TgBot::CallbackQuery);

		cback->message = _message;
		cback->data = core::makeCallback(CBQ_SHOW_PLAYLIST, _message->text);

		plist->setCallbackQuery(cback);
		plist->execute(bot);
		
		return true;
	}
}
