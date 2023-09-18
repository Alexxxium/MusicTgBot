#include "TaskQueueWrapp.h"
#include "InlineCommands.h"
#include "MacroCommands.h"
#include "BotController.h"
#include "AnyCommands.h"
#include "validators.h"
#include "constants.h"
#include "TaskQueue.h"
#include "userdata.h"
#include <iomanip>



static std::mutex mutex;

// 20 queues to async tasks
static algs::TaskQueueWrapper asyncWrap(20);

// id -> atomic flag(wait/not wait response from server), buffer (args to server)
static std::unordered_map<int64_t, std::pair<std::atomic<bool>, std::vector<std::string>>> usersBuffer;

static const std::string serverBusy = mb::core::parseHTML(mb::pth::MESSAGE_DIR + mb::pth::HTML_WAIT_SERVER_RESP);




namespace mb::cmd::any
{
	bool CreatePlayList::execute(TgBot::Bot &bot) const {
		const int64_t &id = _message->chat->id;
		const std::string &plist = _message->text;

		if (!core::isValidPath(plist, pth::SUB_DIR_TO_PLIST, id, bot)) {
			return false;
		}

		core::create(id, plist);

		bot.getApi().sendMessage(id, core::parseHTML(pth::MESSAGE_DIR + pth::HTML_CREATED_PLIST), false, 0, nullptr, mrk::HTML);
		return Execute<mcr::ShowPlayLists>::execute(name(), _message, bot);
	}

	bool RenamePlayList::execute(TgBot::Bot &bot) const {
		const int64_t &id = _message->chat->id;
		const std::string &plist = _message->text;

		if (!core::isValidPath(plist, pth::SUB_DIR_TO_PLIST, id, bot)) {
			return false;
		}

		core::rename(id, _name, plist);

		return Execute<inl::PListPressed>::execute(CBQ_SHOW_PLAYLIST, _message, bot, 
			core::makeCallback(CBQ_SHOW_PLAYLIST, plist)
		);
	}

	bool RenameTrack::execute(TgBot::Bot &bot) const {
		const std::string
			&track = _message->text,
			&oldtr = _name,
			&newtr = core::replace(oldtr, track);
		const int64_t &id = _message->chat->id;


		if (!core::isValidPath(newtr, pth::SUB_DIR_TO_TRACK, id, bot)) {
			return false;
		}

		core::rename(id, oldtr, newtr);

		return Execute<inl::TrackPressed>::execute(track, _message, bot, 
			core::makeCallback(CBQ_SHOW_TRACK, newtr)
		);
	}




	void asyncDownloader(int64_t id, int entry, int ms) {
		auto &it = usersBuffer.find(id);

		if (it == usersBuffer.end()) {
			std::cout << "collision~\n";
			return;
		}

		auto &flag = it->second.first;
		auto &buffer = it->second.second;

		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));

			std::lock_guard<std::mutex> lock(mutex);
			if (buffer.size() == entry) {
				flag.store(true);

				auto ctrl = BotController::getInstanse();
				if (ctrl != nullptr) {
					std::cout << "Response:\t" << ctrl->forward(core::makeServerCmd("douwnload", buffer));
				}

				buffer.clear();
				break;
			}

			entry = buffer.size();
		}

		flag.store(false);
	}

	bool DownloadTrack::execute(TgBot::Bot &bot) const {
		const auto &audio = _message->audio;
		const int64_t &id = _message->chat->id;
		
		if (usersBuffer.find(id) == usersBuffer.end()) {
			usersBuffer[id].first.store(false);
		}

		auto &pair = usersBuffer.find(id)->second;

		if (pair.first.load()) {
			bot.getApi().sendMessage(id, serverBusy, false, 0, nullptr, mrk::HTML);
			return false;
		}
		if (audio) {
			const auto &file = bot.getApi().getFile(audio->fileId);

			std::lock_guard<std::mutex> lock(mutex);
			if (pair.second.size() == 0) {
				int entry = pair.second.size();
				asyncWrap.addToFreeQueue([=]() { asyncDownloader(id, entry, 500); });
			}
			pair.second.push_back(file->filePath);
		}

		return false;
	}
}
