#include "pidcpu.h"

PidCPU::PidCPU(std::string pId)
{
    pid = pId;
}

void PidCPU::calculatePidCPU(){
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

void PidCPU::callUsage(){
	while(1){
		calculatePidCPU();
		sleep(1);
	}
}

double PidCPU::getPidCPU()
{
    return cpu_usage;
}

void PidCPU::runThread(){
	pid_t = std::thread(&PidCPU::callUsage, this);
}
