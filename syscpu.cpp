#include "syscpu.h"

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
};

struct prev_procStat{
	double prev_idle = 0;
	double prev_iowait = 0;
	double prev_user = 0;
	double prev_nice = 0;
	double prev_system = 0;
	double prev_irq = 0;
	double prev_softirq = 0;
	double prev_steal = 0;
};

SysCPU::SysCPU()
{

}

SysCPU::~SysCPU(){
	if(syscpu_thr.joinable()){
		stopThread();
	}
}

void SysCPU::calculate_usage()
{
	procStat inf;
	prev_procStat pInf;

	char filePath[50] = "/proc/stat";
	std::ifstream fileStat;
	fileStat.open(filePath, std::ios_base::in);
	std::string word;

	int count = 0;

	while(fileStat >> word){
		count++;

		if(count == proc::eUser){
			inf.user = std::stod(word);
		}
		else if(count == proc::eNice){
			inf.nice = std::stod(word);
		}
		else if(count == proc::eSystem){
			inf.system = std::stod(word);
		}
		else if(count == proc::eIdle){
			inf.idle = std::stod(word);
		}
		else if(count == proc::eIowait){
			inf.iowait = std::stod(word);
		}
		else if(count == proc::eIrq){
			inf.irq = std::stod(word);
		}
		else if(count == proc::eSoftirq){
			inf.softirq = std::stod(word);
		}
		else if(count == proc::eSteal){
			inf.steal = std::stod(word);
		}
		else{

		}
	}

	fileStat.close();

	double prevIdle = pInf.prev_idle + pInf.prev_iowait;
	double prevNonIdle = pInf.prev_user + pInf.prev_nice + pInf.prev_system + pInf.prev_irq + pInf.prev_softirq + pInf.prev_steal;
	double prevTotal = prevIdle + prevNonIdle;

	double idle = inf.idle - inf.iowait;
	double nonIdle = inf.user + inf.nice + inf.system + inf.irq + inf.softirq + inf.steal;
	double total = idle + nonIdle;

	double totald = total - prevTotal;
	double idled = idle - prevIdle;

	totalCPU_percentage = (totald - idled) / totald;
}

double SysCPU::getSysCPU(){
	return totalCPU_percentage;
}

bool SysCPU::callUsage(){
	while(stop_bool){
		{
			std::unique_lock <std::mutex> lock_usage(mutex_pid);
			cv.wait_for(lock_usage, std::chrono::seconds(1));
			if (!stop_bool){
				break;
			}
		}
		calculate_usage();
	}
	return stop_bool;
}

void SysCPU::runThread(){
	syscpu_thr = std::thread(&SysCPU::callUsage, this);
}

void SysCPU::stopThread(){
	stop_bool = false;
	cv.notify_one();
	syscpu_thr.join();
}
