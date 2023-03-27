#ifndef PIDCPU_H
#define PIDCPU_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cstring>
#include <unistd.h>
#include <map>
#include <thread>
#include <chrono>

enum proc_stat{
    pIdle = 11,
    uTime,
    sTime,
    cuTime,
    csTime,
    startTime = 20
};

struct cpu_info{
    double utime;     //14 user code harcanan clock ticks
    double stime;     //15 kernel code harcanan clock ticks
    double cutime;    //16 in user code waited for childrens cpu time spent
    double cstime;    //17 in kernel code
    double starttime; //22
    double uptime;
};

class PidCPU
{
private:
    std::string pid = "";
    double seconds = 0;
    double hertz = sysconf(_SC_CLK_TCK);
    double total_time = 0;
    double cpu_usage;

	std::thread pid_t;

public:
    PidCPU(std::string pId);
	void calculatePidCPU();
	void callUsage();
    double getPidCPU();
	void runThread();
};

#endif // PIDCPU_H


