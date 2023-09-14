#include <iostream>
#include "ServerQueues.h"
#include "ServerConstants.h"
#include "ServerOperations.h"
#include <tgbot/tgbot.h>



int main()
{
	auto queues = srv::ServerQueues::getInstanse(srv::init::QUEUES_COUNT);
	queues->assept("upload_group 710890997 sas");
	//queues->assept("upload 710890997 sas/sas.mp3");


	std::cout << "Listening semulation...\n";
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}