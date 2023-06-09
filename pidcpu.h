#ifndef PIDCPU_H
#define PIDCPU_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <cpumem_usage.h>

class PidCPU : public CpuMem_Usage
{
public:
	PidCPU();
	~PidCPU();
	void setPid(std::string pId);
	double getPidCPU();
	void runThread();

private:
    std::string pid = "";
    double seconds = 0;
    double hertz = sysconf(_SC_CLK_TCK);
    double total_time = 0;
    double cpu_usage;
	bool stop_bool = true;
	std::thread pidcpu_thr;
	std::mutex mutex_pid;
	std::condition_variable cv;

	void calculate_usage();
	bool callUsage();
	void stopThread();
};

#endif // PIDCPU_H


