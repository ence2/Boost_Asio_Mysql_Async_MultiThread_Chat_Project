#include "pch.h"

int main()
{	
	ThreadPool test(5);
	DBManager::Instance().Init();

	TCP_Server::instance().Run();

	std::cout << "Server Down" << std::endl;
	getchar();
}