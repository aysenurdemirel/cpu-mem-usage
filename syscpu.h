#ifndef SYSCPU_H
#define SYSCPU_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>

enum proc{
    eUser = 2,
    eNice,
    eSystem,
    eIdle,
    eIowait,
    eIrq,
    eSoftirq,
    eSteal,
};

struct procStat{
    double user;
    double nice;
    double system;
    double idle;
    double iowait;
    double irq;
    double softirq;
    double steal;
    double totalCPU_percentage;
};


class SysCPU
{
private:
    double prev_idle = 0;
    double prev_iowait = 0;
    double prev_user = 0;
    double prev_nice = 0;
    double prev_system = 0;
    double prev_irq = 0;
    double prev_softirq = 0;
    double prev_steal = 0;

    double totalCPU_percentage = 0;

	std::thread sys_t;

public:
	SysCPU();
	void calculateSysCPU();
	void callUsage();
	double getSysCPU();
	void runThread();

};

#endif // SYSCPU_H
