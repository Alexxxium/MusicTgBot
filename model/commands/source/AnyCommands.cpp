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

static TgBot::Bot asyncBot(mb::init::TOKEN);

// 20 queues to async tasks
static algs::TaskQueueWrapper asyncWrap(20);

// id -> atomic flag(wait/not wait response from server), buffer (args to server)
static std::unordered_map<int64_t, std::pair<std::atomic<bool>, std::list<std::string>>> usersBuffer;

static const std::string serverBusy = mb::core::parseHTML(mb::pth::MESSAGE_DIR + mb::pth::HTML_WAIT_SERVER_RESP);
static const std::string waitSendind = mb::core::parseHTML(mb::pth::MESSAGE_DIR + mb::pth::HTML_WAIT_SEND_TO_SRV);




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




	void asyncDownloader(int64_t id, const std::string &plist, int entry, int ms) {
		constexpr auto srvcmd = "download", sep = "\n";
		constexpr int maxlen = 5;

		auto &it = usersBuffer.find(id);
		if (it == usersBuffer.end()) {
			throw std::runtime_error("End-iterator!");
			return;
		}

		auto &flag = it->second.first;
		auto &buffer = it->second.second;

		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));

			std::lock_guard<std::mutex> lock(mutex);
			if (buffer.size() == entry) {
				flag.store(true);

				if (buffer.size() > maxlen) {
					buffer.resize(maxlen);
				}

				std::string text = waitSendind;
				for (const auto &fname: buffer) {
					text += sep + fname.substr(0, fname.find("|"));
				}
				asyncBot.getApi().sendMessage(id, text, false, 0, nullptr, mrk::HTML);

				auto ctrl = BotController::getInstanse();

				if (ctrl != nullptr) {
					std::vector<std::string> args(buffer.begin(), buffer.end());
					const auto &config = core::makeServerCmd(core::makeServerCmd(srvcmd, { std::to_string(id), plist }), args);

					std::string response = ctrl->forward(config);
					core::lockToResponse(response, id, plist);

					asyncBot.getApi().sendMessage(id, response, false, 0, nullptr, mrk::HTML);
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

		auto &it = usersBuffer.find(id)->second;
		auto &flag = it.first;
		auto &buffer = it.second;

		if (flag.load()) {
			//bot.getApi().sendMessage(id, serverBusy, false, 0, nullptr, mrk::HTML);
			return false;
		}
		if (audio) {
			std::lock_guard<std::mutex> lock(mutex);
			if (buffer.size() == 0) {
				int entry = buffer.size();
				std::string plist = _name;
				asyncWrap.addToFreeQueue([=]() {
					asyncDownloader(id, plist, entry, 500);
				});
			}
			std::string srvarg = core::makeServerCmd(audio->fileName, { audio->fileId });
			buffer.push_back(srvarg);
		}

		return false;
	}




	bool DownloadTrackFromURL::execute(TgBot::Bot &bot) const {
		constexpr int maxlen = 5;
		constexpr auto cmd = "url_upload";
		const int64_t &id = _message->chat->id;

		if (core::checkLock(id, "")) {
			bot.getApi().sendMessage(id, serverBusy, false, 0, nullptr, mrk::HTML);
			return false;
		}

		std::stringstream stream(_message->text);
		std::vector<std::string> args;

		while (stream && args.size() < maxlen) {
			std::string buff;
			stream >> buff;
			if (core::isURL(buff)) {
				args.push_back(buff);
			}
		}
		if (args.empty()) {
			return false;
		}
		
		auto ctrl = BotController::getInstanse();
		std::string srvcmd = core::makeServerCmd(core::makeServerCmd(cmd, { std::to_string(id) }), args);

		if (ctrl == nullptr) {
			throw err::NULL_INSTANSE;
		}

		std::string response = ctrl->forward(srvcmd);
		core::lockToResponse(response, id, "");
		bot.getApi().sendMessage(_message->chat->id, response, false, 0, nullptr, mrk::HTML);
		return false;
	}
}
