#include "AnyCommands.h"
#include "constants.h"
#include "parsers.h"
#include <filesystem>
#include <locale>
#include <codecvt>
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
		constexpr auto regexstr = L"^[a-zA-Z0-9_\ а-яА-яёЁ]+$";
		constexpr int maxlen = 25;
		std::wregex valid(regexstr);

		
		// Создаем объект локали для UTF-8
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

		// Преобразуем строку в wstring с помощью wstring_convert
		std::wstring utf16String = converter.from_bytes(_message->text);



		if (_message->text.size() > maxlen) {
			bot.getApi().sendMessage(_message->chat->id, "More 25!");
			return false;
		}
		if (!std::regex_search(utf16String, valid)) {
			bot.getApi().sendMessage(_message->chat->id, "INVALID");
			return false;
		}
		
		
		std::string path = pth::USER_DATA_DIR + std::to_string(_message->chat->id) + "/" + _message->text;
		if (fs::exists(path)) {
			bot.getApi().sendMessage(_message->chat->id, "No!");
			return false;
		}
		fs::create_directory(path);
		bot.getApi().sendMessage(_message->chat->id, "Playlist created!");
		return true;
	}

	bool ValidatePListName::execute(TgBot::Bot &bot) const {
		constexpr auto regexstr = "^[a-zA-Z0-9_-]+$";
		std::regex valid(regexstr);

		if (std::regex_search(_message->text, valid)) {
			std::cout << "Creating playlist\n";
		}
		else {
			std::cout << "ban\n";
		}

		return true;
	}
}
