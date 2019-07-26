#pragma once
#include "pch.h"

class ThreadPool;

// our worker thread objects
class Worker {
public:
	Worker(ThreadPool &s) : pool(s) {  }
	void operator()();
	std::string Id;
private:
	ThreadPool &pool;
};

// the actual thread pool
class ThreadPool {
public:
	ThreadPool(size_t);
	template<class F>
	void enqueue(F f);
	~ThreadPool();
private:
	friend class Worker;

	// need to keep track of threads so we can join them
	std::vector< std::thread > workers;

	// the task queue
	std::deque< std::function<void()> > tasks;

	// synchronization
	std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop;
};

template<class F>
void ThreadPool::enqueue(F f)
{
	{ // acquire lock
		std::unique_lock<std::mutex> lock(queue_mutex);

		// add the task
		tasks.push_back(std::function<void()>(f));
	} // release lock

	// wake up one thread
	condition.notify_one();
}
