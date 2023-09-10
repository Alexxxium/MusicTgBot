#include "ServerQueues.h"



namespace srv
{
	ServerQueues* ServerQueues::singleton = nullptr;

	ServerQueues::ServerQueues(const std::initializer_list<int> &idlist) {
		for (int id: idlist) {
			taskstable[id] = new algs::TaskQueue;
		}
	}

	ServerQueues* ServerQueues::getInstance(const std::initializer_list<int> &idlist) {
		if (!singleton) {
			singleton = new ServerQueues(idlist);
		}
		return singleton;
	}

	void ServerQueues::addTask(int key, const std::function<void()> &task) {
		const auto &it = taskstable.find(key);

		if (it == taskstable.end()) {
			throw 1;
		}

		auto &queue = it->second;
		queue->addTask(task);
	}
}