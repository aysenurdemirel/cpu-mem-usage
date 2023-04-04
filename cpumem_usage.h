#ifndef CPUMEM_USAGE_H
#define CPUMEM_USAGE_H

#include <iostream>

class CpuMem_Usage
{
public:
	CpuMem_Usage();

	virtual void runThread();
	virtual void stopThread();
	virtual bool callUsage();
	virtual void calculate_usage();

private:
	bool stop_bool = true;
};

#endif // CPUMEM_USAGE_H
