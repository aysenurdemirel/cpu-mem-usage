#ifndef PIDMEM_H
#define PIDMEM_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <cpumem_usage.h>

class PidMem : public CpuMem_Usage
{
public:
	PidMem();
	~PidMem();
	void setPid(std::string pId);
	double getPidMemVm();
	double getPidMemRss();
	void runThread();

private:
	std::string pid = "";
	double vm_usage = 0;
	double resident_set = 0;
	double page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;
	bool stop_bool = true;
	std::thread pidmem_thr;
	std::mutex mutex_pid;
	std::condition_variable cv;

	void calculate_usage();
	bool callUsage();
	void stopThread();
};

#endif // PIDMEM_H
