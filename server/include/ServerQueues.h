#pragma once
#include "TaskQueue.h"



namespace srv
{
	/// Create N algs::TaskQueue and monitors uniformity in queues
	/// Recommended to use equivalent time tasks (only downloads or only uploads)
	class LocalQueueWrapper {
	private:
		std::vector<std::unique_ptr<algs::TaskQueue>> queues;

	public:
		LocalQueueWrapper() = delete;
		~LocalQueueWrapper() = default;
		LocalQueueWrapper(LocalQueueWrapper&&) = delete;
		LocalQueueWrapper(const LocalQueueWrapper&) = delete;
		LocalQueueWrapper& operator=(LocalQueueWrapper&&) = delete;
		LocalQueueWrapper& operator=(const LocalQueueWrapper&) = delete;

		explicit LocalQueueWrapper(const int &len);

		int getFreeQueue() const noexcept;

		void addToQueue(const int &index, const std::function<void()> &handler);
		void addToQueue(const int &index, const std::initializer_list<std::function<void()>> &handlers);

		void addToFreeQueue(const std::function<void()> &handler);
		void addToFreeQueue(const std::initializer_list<std::function<void()>> &handlers);
	};


	
	/// Tasks distributor
	class ServerQueues {
	private:
		static ServerQueues *singleton;
		std::unordered_map<std::string, std::unique_ptr<LocalQueueWrapper>> taskports;

		explicit ServerQueues(const std::unordered_map<std::string, int> &cmdlet);
		std::function<void()> getHandler(const std::string &servcmd);

	public:
		ServerQueues() = delete;
		~ServerQueues() = default;
		ServerQueues(ServerQueues&&) = delete;
		ServerQueues(const ServerQueues&) = delete;
		ServerQueues& operator=(ServerQueues&&) = delete;
		ServerQueues& operator=(const ServerQueues&) = delete;

		static ServerQueues* getInstanse(const std::unordered_map<std::string, int> &cmdlet) noexcept;
	};
}