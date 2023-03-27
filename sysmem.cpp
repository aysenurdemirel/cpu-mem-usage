#include "sysmem.h"

SysMem::SysMem()
{

}

void SysMem::calculateSysMem()
{
    memory_info mInf;

    char filePath[50] = "/proc/meminfo";
    std::ifstream meminfo;
    meminfo.open(filePath, std::ios_base::in);
    std::string word;

    int count = 0;

    while(getline(meminfo, word)){
        count ++;

        std::string ikinokta = ":    ";
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

void SysMem::callUsage(){
	while(1){
		calculateSysMem();
		sleep(1);
	}
}

double SysMem::getSysMem()
{
    return memory_utilized;
}

void SysMem::runThread(){
	mem_t = std::thread(&SysMem::callUsage, this);
}
