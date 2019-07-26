#pragma once
#include "pch.h"

class DBJobQ : public JobQueueThreading
{
public:
	DBJobQ();
	~DBJobQ();

	static DBJobQ& Instance();
};

