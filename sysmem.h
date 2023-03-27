#ifndef SYSMEM_H
#define SYSMEM_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>

enum eMemory{
    eTotal = 1,
    eAvailable = 3
};

struct memory_info{
    double total;
    double available;
};

class SysMem
{
private:
    double memory_utilized;
	std::thread mem_t;

public:
	SysMem();
	void calculateSysMem();
	void callUsage();
	double getSysMem();
	void runThread();
};

#endif // SYSMEM_H
