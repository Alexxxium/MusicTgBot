#include <unordered_map>
#include "TaskQueue.h"


namespace srv
{
	class ServerQueues
	{
	private:
		static ServerQueues *singleton;

		std::unordered_map<int, algs::TaskQueue*> taskstable;

		explicit ServerQueues(const std::initializer_list<int> &idlist);

	public:
		static ServerQueues* getInstance(const std::initializer_list<int> &idlist);

		void addTask(int key, const std::function<void()> &task);
	};
}