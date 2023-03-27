#include <pidcpu.h>
#include <sysmem.h>
#include <syscpu.h>
#include <thread>
#include <functional>

int main(int argc, char* argv[])
{
    PidCPU objP = PidCPU(argv[1]);
	SysCPU objT;
	SysMem objM;

	objP.runThread();
	objT.runThread();
	objM.runThread();

    while(1){
		std::cout << "memory_utilized:: %" << objM.getSysMem() << std::endl;

		if(argc <= 1 || std::stod(argv[1]) < 0){
			std::cout << "System_CPU: %" << objT.getSysCPU() << std::endl << std::endl;
        }
        else {
            std::cout << "pid_CPU: %" << objP.getPidCPU() << std::endl << std::endl;
        }

		sleep(5);
    }
}

//run thread olacak threadler orada saniyede bir dönecek
// main de istediği sürede çalıştıracak


// utime ve stime için after before yap belki olur

/*
gencler yarin da thread e bakiyorsunuz
sonra cpu olcme projenizde thread ekleyeceksiniz
her saniye cpu olcup saklayacak her class kendi icinde ben istedigim zaman alacagim usage i

ve pzt ye 2nizin de github hesabi acip oraya cpu projesini guzel bir sekilde atmaniz lazim
*/
