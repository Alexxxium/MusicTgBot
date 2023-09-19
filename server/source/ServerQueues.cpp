#include "ServerQueues.h"
#include "ServerData.h"
#include "ServerConstants.h"
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <iostream>


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

	void ServerQueues::accept(std::string &&cmd) {
		constexpr int notation_args_len = 2;

		const auto &args = split(std::move(cmd), "|");

		if (args.size() < notation_args_len) {
			throw err::INVALID_NOTATION;
		}
		
		std::string name = args[0];
		const auto &port = taskports.find(name);
		const auto &handl = init::HANDLERS.find(name);

		if (port == taskports.end() || handl == init::HANDLERS.end()) { 
			throw err::UNKOWN_CMD;
		}

		port->second->addToFreeQueue(handl->second->executor(args));
	}
}
