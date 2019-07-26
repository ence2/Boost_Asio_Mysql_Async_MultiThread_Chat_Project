#pragma once
#include "pch.h"

class JobQueueThreading
{
	std::thread *worker = nullptr;
	std::queue<Job*> jobQ;
	std::mutex mtx;
	
	std::string poolType_;

	void Process();
public:
	JobQueueThreading(std::string);
	~JobQueueThreading();

	void Queue(Job job);
};

