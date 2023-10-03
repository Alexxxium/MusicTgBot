#include "Server.h"
#include <iostream>



int main()
{
	try {
		srv::Server server;
		server.listening();
	}
	catch (const std::exception &err) {
		std::cout << "-s error:\t" << err.what() << std::endl;
	}
	catch(...) {
		std::cout << "-u error:\t" << "Unknown error!" << std::endl;
	}
	system("pause");
}