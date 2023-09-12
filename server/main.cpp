#include <iostream>
#include "ServerQueues.h"
#include "ServerOperations.h"
#include <tgbot/tgbot.h>



void f(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); std::cout << std::this_thread::get_id() << " ended\n"; };

void testLocalQueue() {
	srv::LocalQueueWrapper wrapp(3);

	TgBot::Bot bot("6282754512:AAFaF5Gfi3uTTgNRndN8y3c3xac2y7b-25U");

	wrapp.addToQueue(0, []() { f(3000); });
	wrapp.addToQueue(0, []() { f(1000); });
	wrapp.addToQueue(0, []() { f(1000); });
	//wrapp.addToQueue(0, []() { f(1000); });
	//wrapp.addToQueue(0, []() { f(1000); });
	//wrapp.addToQueue(0, []() { f(1000); });
	//wrapp.addToQueue(0, []() { f(1000); });
	//wrapp.addToQueue(0, []() { f(1000); });
	//wrapp.addToQueue(0, []() { f(1000); });
	//wrapp.addToQueue(0, []() { f(1000); });
	//wrapp.addToQueue(0, []() { f(1000); });

	wrapp.addToQueue(1, []() { f(3000); });
	wrapp.addToQueue(1, []() { f(1000); });
	wrapp.addToQueue(1, []() { f(1000); });
	//wrapp.addToQueue(1, []() { f(1000); });
	//wrapp.addToQueue(1, []() { f(1000); });

	wrapp.addToQueue(2, []() { f(3000); });
	wrapp.addToQueue(2, []() { f(1000); });
	wrapp.addToQueue(2, []() { f(1000); });

	std::cout << "\nLOW\n";

	wrapp.addToFreeQueue({
		[]() { f(1000); std::cout << "FREEEEEE1\n"; },
		[]() { f(1000); std::cout << "FREEEEEE2\n"; },
		[]() { f(1000); std::cout << "FREEEEEE3\n"; },
		[]() { f(1000); std::cout << "FREEEEEE4\n"; },
		[]() { f(1000); std::cout << "FREEEEEE5\n"; },
		[]() { f(1000); std::cout << "FREEEEEE6\n"; },
		[]() { f(1000); std::cout << "FREEEEEE7\n"; },
		[]() { f(1000); std::cout << "FREEEEEE8\n"; },
		[]() { f(1000); std::cout << "FREEEEEE9\n"; }
		});

	std::cout << wrapp.getFreeQueue() << '\n';
}



int main()
{
	std::function<void()> func;

	{
		srv::SendAudio audio;
		func = audio.executor("");
	}
	func();
}