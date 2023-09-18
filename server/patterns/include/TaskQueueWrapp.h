#pragma once
#include "TaskQueue.h"



namespace algs 
{
/// Create N algs::TaskQueue and monitors uniformity in queues
/// Recommended to use equivalent time tasks (only downloads or only uploads)
	class TaskQueueWrapper {
	private:
		std::vector<std::unique_ptr<algs::TaskQueue>> queues;

	public:
		TaskQueueWrapper() = delete;
		~TaskQueueWrapper() = default;
		TaskQueueWrapper(TaskQueueWrapper&&) = delete;
		TaskQueueWrapper(const TaskQueueWrapper&) = delete;
		TaskQueueWrapper& operator=(TaskQueueWrapper&&) = delete;
		TaskQueueWrapper& operator=(const TaskQueueWrapper&) = delete;

		explicit TaskQueueWrapper(const int &len);

		// Returns the smallest queue by length 
		int getFreeQueue() const noexcept;

		void addToQueue(const int &index, const std::function<void()> &handler);
		void addToQueue(const int &index, const std::initializer_list<std::function<void()>> &handlers);

		void addToFreeQueue(const std::function<void()> &handler);
		void addToFreeQueue(const std::initializer_list<std::function<void()>> &handlers);
	};
};