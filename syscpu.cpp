#include "syscpu.h"

SysCPU::SysCPU()
{

}

void SysCPU::calculateSysCPU()
{
	procStat inf;

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

	double prevIdle = prev_idle + prev_iowait;
	double prevNonIdle = prev_user + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal;
	double prevTotal = prevIdle + prevNonIdle;

	double idle = inf.idle - inf.iowait;
	double nonIdle = inf.user + inf.nice + inf.system + inf.irq + inf.softirq + inf.steal;
	double total = idle + nonIdle;

	double totald = total - prevTotal;
	double idled = idle - prevIdle;

	totalCPU_percentage = (totald - idled) / totald;
}

void SysCPU::callUsage(){
	while(1){
		calculateSysCPU();
		sleep(1);
	}
}

double SysCPU::getSysCPU()
{
	return totalCPU_percentage;
}

void SysCPU::runThread(){
	sys_t = std::thread(&SysCPU::callUsage, this);
}
