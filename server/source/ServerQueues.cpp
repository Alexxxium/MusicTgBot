#include "ServerQueues.h"
#include "ServerConstants.h"
#include <sstream>
#include <map>



namespace srv
{
	LocalQueueWrapper::LocalQueueWrapper(const int &len) {
		if (len <= 0) {
			throw err::INVALID_QUEUE_SIZE;
		}
		queues.reserve(len);

		for (int i = 0; i < len; ++i) {
			queues.push_back(std::make_unique<algs::TaskQueue>());
		}
	}

	int LocalQueueWrapper::getFreeQueue() const noexcept {
		int min = INT_MAX;
		int res = -1;

		for (int i = 0; i < queues.size(); ++i) {
			if (queues[i]->size() < min) {
				min = queues[i]->size();
				if (min == 0) {
					return i;
				}
				res = i;
			}
		}
		return res;
	}



	void LocalQueueWrapper::addToQueue(const int &index, const std::function<void()> &handler) {
		if (index < 0 || index >= queues.size()) {
			throw err::INVALID_INDEX;
		}
		queues[index]->addTask(handler);
	}

	void LocalQueueWrapper::addToQueue(const int &index, const std::initializer_list<std::function<void()>> &handlers) {
		if (index < 0 || index >= queues.size()) {
			throw err::INVALID_INDEX;
		}
		queues[index]->addTasks(handlers);
	}



	// O(n)
	void LocalQueueWrapper::addToFreeQueue(const std::function<void()> &handler) {
		int port = getFreeQueue();

		if (port < 0) {
			throw err::INVALID_INDEX;
		}
		queues[port]->addTask(handler);
	}

	// O(N * log(N) + K), K - handlers count
	void LocalQueueWrapper::addToFreeQueue(const std::initializer_list<std::function<void()>> &handlers) {
		if (queues.size() == 0) {
			throw err::INVALID_QUEUE_SIZE;
		}
		else if (queues.size() == 1) {
			queues[0]->addTasks(handlers);
			return;
		}

		std::multimap<size_t, int> map;                            // <queue.size(), index in queueS>
		for (int i = 0; i < queues.size(); ++i) {
			map.insert({ queues[i]->size(), i });
		}

		auto curr = map.begin();
		auto next = std::next(curr);
		int count = curr->first;

		// balance inserting into queues
		for (const auto &handler: handlers) {                      
			if (next == map.end()) {
				next = map.begin();
			}
			else if (curr == map.end()) {                          // curr it. will never stay equal next it.
				curr = map.begin();
			}

			if (count <= next->first) {
				queues[curr->second]->addTask(handler);
				++count;
			}
			else {
				queues[next->second]->addTask(handler);
				count = next->first;
				++curr;
				++next;
			}
		}
	}





	ServerQueues* ServerQueues::singleton = nullptr;


	ServerQueues::ServerQueues(const std::unordered_map<std::string, int> &cmdlet) {
		for (const auto &[cmd, count]: cmdlet) {
			taskports[cmd] = std::make_unique<LocalQueueWrapper>(count);
		}
	}

	ServerQueues* ServerQueues::getInstanse(const std::unordered_map<std::string, int> &cmdlet) noexcept {
		if (!singleton) {
			singleton = new ServerQueues(cmdlet);
		}
		return singleton;
	}

	void ServerQueues::assept(const std::string &cmd) {
		std::stringstream stream(cmd);
		std::vector<std::string> args;
		std::string name;

		stream >> name;

		while (stream) {
			std::string buff;
			stream >> buff;
			args.push_back(std::move(buff));
		}

		const auto &port = taskports.find(name);
		const auto &handl = init::HANDLERS.find(name);

		if (port == taskports.end() || handl == init::HANDLERS.end()) { 
			throw err::UNKOWN_CMD;
		}

		port->second->addToFreeQueue(handl->second->executor(args));
	}
}
