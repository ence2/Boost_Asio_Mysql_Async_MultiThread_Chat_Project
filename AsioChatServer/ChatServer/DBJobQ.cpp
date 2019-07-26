#pragma once
#include "pch.h"



DBJobQ::DBJobQ() : JobQueueThreading("DB")
{
}


DBJobQ::~DBJobQ()
{
}

DBJobQ& DBJobQ::Instance()
{
	static DBJobQ _q;
	return _q;
}
