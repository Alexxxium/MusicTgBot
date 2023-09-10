#include <iostream>
#include "TaskQueue.h"


int g = 0;

void sleep(uint64_t ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void st() {
	std::cout << "task:\t" << g << '\n';
}



int main()
{
	algs::TaskQueue queue;

	// task
	const auto& s = [&]() { ++g; std::this_thread::sleep_for(std::chrono::milliseconds(100)); };

	// 50 tasks
	queue.addTasks({
		s,s,s,s,s,s,s,s,s,s,
		s,s,s,s,s,s,s,s,s,s,
		s,s,s,s,s,s,s,s,s,s,
		s,s,s,s,s,s,s,s,s,s,
		s,s,s,s,s,s,s,s,s,s
	});

	// tasks count +- 1

	sleep(1'000);      // ~10 tasks
	st();
	queue.freeze();

	sleep(500);        // ~10 tasks (5 ignore)
	st();
	queue.unfreeze();
	
	sleep(1'000);      // ~20 tasks
	st();
	queue.freeze();

	sleep(500);        // ~25 tasks (5 ignore)
	st();
	queue.crash();

	sleep(500);        // ~30 tasks (5 ignore)
	st();
	queue.run();

	sleep(1'000);      // ~30 tasks
	st();

	queue.wait();
	st();
}