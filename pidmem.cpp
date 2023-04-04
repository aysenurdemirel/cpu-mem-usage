#include "pidmem.h"

enum proc_stat{
	pIdle = 20,
	vsize,
	rss
};

struct cpu_info{
	double vsize;
	double rss;
};

PidMem::PidMem()
{

}

PidMem::~PidMem()
{
	if(pidmem_thr.joinable()){
		stopThread();
	}
}

void PidMem::setPid(std::string pId){
	pid = pId;
}

void PidMem::calculate_usage(){

	cpu_info cpuInfo;

	char filePath[50] = "/proc/";
	strcat(filePath, pid.c_str());
	strcat(filePath, "/stat");

	std::ifstream fileStat;
	fileStat.open(filePath, std::ios_base::in);
	std::string word;

	int count = 0;
	fileStat.ignore(256, ')');

	while(fileStat >> word){
		count++;

		if(count == proc_stat::vsize){
			 cpuInfo.vsize = std::stod(word) ;
		 }
		 else if(count == proc_stat::rss){
			 cpuInfo.rss = std::stod(word) ;
		 }
		 else{

		 }
	}

	fileStat.close();

	vm_usage = cpuInfo.vsize / 1024;
	resident_set = cpuInfo.rss * page_size_kb;
}

bool PidMem::callUsage(){
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

double PidMem::getPidMemVm(){
	return vm_usage;
}

double PidMem::getPidMemRss(){
	return resident_set;
}

void PidMem::runThread(){
	pidmem_thr = std::thread(&PidMem::callUsage, this);
}

void PidMem::stopThread(){
	stop_bool = false;
	cv.notify_one();
	pidmem_thr.join();
}
