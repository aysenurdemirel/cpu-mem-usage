#include "sysmem.h"

enum eMemory{
	eTotal = 1,
	eAvailable = 3
};

struct memory_info{
	double total;
	double available;
};

SysMem::SysMem()
{

}

SysMem::~SysMem()
{
	if(sysmem_thr.joinable()){
		stopThread();
	}
}

void SysMem::calculate_usage()
{
    memory_info mInf;

    char filePath[50] = "/proc/meminfo";
    std::ifstream meminfo;
    meminfo.open(filePath, std::ios_base::in);
    std::string word;

    int count = 0;

    while(getline(meminfo, word)){
        count ++;

		std::string ikinokta = ":";
        std::string cikan = word.substr(0, word.find(ikinokta));
        word.erase(0,cikan.length() + ikinokta.length());

        if(count == eTotal){
            mInf.total = std::stod(word);
        }
        else if(count == eAvailable){
            mInf.available = std::stod(word);
        }
        else{

        }
    }

    meminfo.close();

    memory_utilized = ((mInf.total - mInf.available) / mInf.total) * 100;
}

double SysMem::getSysMem(){
	return memory_utilized;
}

bool SysMem::callUsage(){
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

void SysMem::runThread(){
	sysmem_thr = std::thread(&SysMem::callUsage, this);
}

void SysMem::stopThread(){
	stop_bool = false;
	cv.notify_one();
	sysmem_thr.join();
}
