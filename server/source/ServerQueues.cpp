#include "ServerQueues.h"
#include "ServerConstants.h"
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <unordered_map>


namespace fs = std::filesystem;

namespace srv
{
	ServerQueues* ServerQueues::singleton = nullptr;


	ServerQueues::ServerQueues(const std::unordered_map<std::string, int> &cmdlet) {
		for (const auto &[cmd, count]: cmdlet) {
			taskports[cmd] = std::make_unique<algs::TaskQueueWrapper>(count);
		}
	}

	ServerQueues* ServerQueues::getInstanse(const std::unordered_map<std::string, int> &cmdlet) noexcept {
		if (!singleton) {
			singleton = new ServerQueues(cmdlet);
		}
		return singleton;
	}

	void ServerQueues::accept(const std::string &cmd) {
		constexpr int notation_args_len = 2;

		std::stringstream stream(cmd);
		std::vector<std::string> args;
		std::string name, buff;

		stream >> std::quoted(name);

		while (stream >> std::quoted(buff)) {
			args.push_back(std::move(buff));
			buff.clear();
		}

		if (args.size() < notation_args_len) {
			throw err::INVALID_NOTATION;
		}

		const auto &port = taskports.find(name);
		const auto &handl = init::HANDLERS.find(name);

		if (port == taskports.end() || handl == init::HANDLERS.end()) { 
			throw err::UNKOWN_CMD;
		}

		for (int i = 1; i < args.size(); ++i) {
			std::string path = pth::USER_DATA_DIR + args[0] + "/" + args[i];
			if (!fs::exists(path)) {
				throw err::INVALID_PATH;
			}
		}

		port->second->addToFreeQueue(handl->second->executor(args));
	}
}
