#include "Server.h"
#include <iostream>



int main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "Server...\n";

	try {
		srv::Server server;
		server.listening();
		server.close();
	}
	catch (...) {
		return 1;
	}

	std::cout << "...end\n";
}