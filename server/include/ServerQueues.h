#pragma once
#include "TaskQueue.h"
#include "TaskQueueWrapp.h"



namespace srv
{
	/// Tasks distributor
	class ServerQueues {
	private:
		static ServerQueues *singleton;

		std::unordered_map<std::string, std::unique_ptr<algs::TaskQueueWrapper>> taskports;
		explicit ServerQueues(const std::unordered_map<std::string, int> &cmdlet);

	public:
		ServerQueues() = delete;
		~ServerQueues() = delete;
		ServerQueues(ServerQueues&&) = delete;
		ServerQueues(const ServerQueues&) = delete;
		ServerQueues& operator=(ServerQueues&&) = delete;
		ServerQueues& operator=(const ServerQueues&) = delete;


		static ServerQueues* getInstance(const std::unordered_map<std::string, int> &cmdlet) noexcept;

		// Accept string-command and assigns a handlers
		void accept(std::string &&cmd);
	};
}