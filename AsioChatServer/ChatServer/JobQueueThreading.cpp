#include "pch.h"

void JobQueueThreading::Process()
{
	while (true)
	{
		mtx.lock();
		while (true)
		{
			if (jobQ.empty())
			{
				break;
			}

			std::cout << "ThreadPool pop() : threadID -> " << worker->get_id() << std::endl;
			auto func = jobQ.front();
			(*func)();

			jobQ.pop();
			delete func;
		}

		mtx.unlock();
	}
}

JobQueueThreading::JobQueueThreading(std::string poolType) : poolType_(poolType)
{
	//worker = new std::thread(std::bind(&JobQueueThreading::Process, this));
}

JobQueueThreading::~JobQueueThreading()
{
	
}

void JobQueueThreading::Queue(Job job)
{
	//mtx.lock();

	//jobQ.push(new Job(job));

	//mtx.unlock();
	if (poolType_ == "DB")
	{
		TCP_Server::instance().threadPoolDB.enqueue(job);
	}
	else
	{
		TCP_Server::instance().threadPoolJob.enqueue(job);
	}
}
