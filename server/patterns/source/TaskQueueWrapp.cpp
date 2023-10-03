#include "TaskQueueWrapp.h"
#include <map>



namespace algs
{
	TaskQueueWrapper::TaskQueueWrapper(const int &len) {
		if (len <= 0) {
			throw std::runtime_error("Invalid queue size");
		}
		queues.reserve(len);

		for (int i = 0; i < len; ++i) {
			queues.push_back(std::make_unique<algs::TaskQueue>());
		}
	}

	int TaskQueueWrapper::getFreeQueue() const noexcept {
		size_t min = SIZE_MAX;
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



	void TaskQueueWrapper::addToQueue(const int &index, const std::function<void()> &handler) {
		if (index < 0 || index >= queues.size()) {
			throw std::runtime_error("Invalid index!");
		}
		queues[index]->addTask(handler);
	}

	void TaskQueueWrapper::addToQueue(const int &index, const std::initializer_list<std::function<void()>> &handlers) {
		if (index < 0 || index >= queues.size()) {
			throw std::runtime_error("Invalid index!");
		}
		queues[index]->addTasks(handlers);
	}



	// O(n)
	void TaskQueueWrapper::addToFreeQueue(const std::function<void()> &handler) {
		int port = getFreeQueue();

		if (port < 0) {
			throw std::runtime_error("Invalid index!");
		}
		queues[port]->addTask(handler);
	}

	// O(N * log(N) + K), K - handlers count
	void TaskQueueWrapper::addToFreeQueue(const std::initializer_list<std::function<void()>> &handlers) {
		if (queues.size() == 0) {
			throw std::runtime_error("Invalid queue size");
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
		for (const auto &handler : handlers) {
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
}