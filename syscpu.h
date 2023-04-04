#ifndef SYSCPU_H
#define SYSCPU_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <cpumem_usage.h>

class SysCPU : public CpuMem_Usage
{
public:
	SysCPU();
	~SysCPU();
	double getSysCPU();
	void runThread();


private:
	double totalCPU_percentage = 0;
	bool stop_bool = true;
	void calculate_usage();
	bool callUsage();
	void stopThread();

	std::thread syscpu_thr;
	std::mutex mutex_pid;
	std::condition_variable cv;

};

#endif // SYSCPU_H
