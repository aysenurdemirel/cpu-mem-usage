#ifndef SYSMEM_H
#define SYSMEM_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <cpumem_usage.h>

class SysMem : public CpuMem_Usage
{
public:
	SysMem();
	~SysMem();
	double getSysMem();
	void runThread();



private:
	void calculate_usage();
	bool callUsage();
	void stopThread();

    double memory_utilized;
	bool stop_bool = true;
	std::thread sysmem_thr;
	std::mutex mutex_pid;
	std::condition_variable cv;
};

#endif // SYSMEM_H
