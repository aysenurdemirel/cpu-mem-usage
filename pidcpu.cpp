#include "pidcpu.h"

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

PidCPU::PidCPU()
{

}

PidCPU::~PidCPU()
{
	if(pidcpu_thr.joinable()){
		stopThread();
	}
}

void PidCPU::setPid(std::string pId){
	pid = pId;
}

void PidCPU::calculate_usage(){
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

        if(count == proc_stat::uTime){
             cpuInfo.utime = std::stod(word) ;
         }
         else if(count == proc_stat::sTime){
             cpuInfo.stime = std::stod(word) ;
         }
         else if(count == proc_stat::cuTime){
             cpuInfo.cutime = std::stod(word) ;
         }
         else if(count == proc_stat::csTime){
             cpuInfo.cstime = std::stod(word) ;
         }
         else if(count == proc_stat::startTime){
             cpuInfo.starttime = std::stod(word) ;
         }
         else{

         }
    }

    fileStat.close();

    char uptimePath[50] = "/proc/uptime";
    std::ifstream fileUptime;
    fileUptime.open(uptimePath);
    std::string uptime_str;
    fileUptime >> uptime_str;

    cpuInfo.uptime = std::stod(uptime_str);

    total_time = total_time + cpuInfo.utime + cpuInfo.stime;
    seconds = cpuInfo.uptime - ((cpuInfo.uptime - cpuInfo.starttime) / hertz);
    cpu_usage = 100 * (total_time / hertz) / seconds;

    fileUptime.close();
}

bool PidCPU::callUsage(){
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

double PidCPU::getPidCPU(){
    return cpu_usage;
}

void PidCPU::runThread(){
	pidcpu_thr = std::thread(&PidCPU::callUsage, this);
}

void PidCPU::stopThread(){
	stop_bool = false;
	cv.notify_one();
	pidcpu_thr.join();
}
