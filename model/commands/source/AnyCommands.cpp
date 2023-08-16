#include "AnyCommands.h"
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
		auto &it = buffer.find(message->chat->id);

		if (it == buffer.end()) {
			return nullptr;
		}
		else if (core::prefixCmd(it->second) == std::to_string(CBQ_ADD_PLAYLIST)) {
			return new CreatePlayList("");
		}

		return nullptr;
	}


	bool CreatePlayList::execute(TgBot::Bot &bot) const
	{
		constexpr int 
			maxlen = 25, 
			minlen = 1;
		const auto &text = _message->text;
		const auto &id   = _message->chat->id;
		std::string path = pth::USER_DATA_DIR + std::to_string(id) + "/" + text;

		if (_message->text.size() > maxlen) {
			bot.getApi().sendMessage(id, "More 25!");
			return false;
		}
		if (_message->text.size() < minlen) {
			bot.getApi().sendMessage(id, "Lower 1!");
			return false;
		}
		if (core::isValidName(text)) {
			bot.getApi().sendMessage(id, "INVALID");
			return false;
		}
		if (fs::exists(path)) {
			bot.getApi().sendMessage(id, "Existed!");
			return false;
		}
		core::createPlaylist(id, text);
		bot.getApi().sendMessage(id, "Playlist created!");

		return true;
	}
}
