#include <pidcpu.h>
#include <pidmem.h>
#include <sysmem.h>
#include <syscpu.h>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <cpumem_usage.h>

int main(int argc, char* argv[])
{
	PidCPU objPC;
	PidMem objPM;
	SysCPU objSC;
	SysMem objSM;
	CpuMem_Usage* obj_cpumem = new CpuMem_Usage;

	int count = 0;

	if(argc > 1){
		obj_cpumem = &objPC;
		obj_cpumem->runThread();
		objPC.setPid(argv[1]);

		obj_cpumem = &objPM;
		obj_cpumem->runThread();
		objPM.setPid(argv[1]);


	}

	else{
		obj_cpumem = &objSC;
		obj_cpumem->runThread();

		obj_cpumem = &objSM;
		obj_cpumem->runThread();
	}

	while(1){
		count++;

		if(argc > 1){			
			std::cout << "Pid CPU Usage: %" << objPC.getPidCPU() << std::endl;
			std::cout << "Pid Mem Usage: " << objPM.getPidMemVm() << std::endl;
			std::cout << "Resident Set Size: " << objPM.getPidMemRss() << std::endl << std::endl;

			if(count == 10){
				obj_cpumem = &objPC;
				obj_cpumem->stopThread();

				obj_cpumem = &objPM;
				obj_cpumem->stopThread();
				break;
			}
		}

		else {
			std::cout << "System CPU Usage: %" << objSC.getSysCPU() << std::endl;
			std::cout << "System Memory Usage: %" << objSM.getSysMem() << std::endl << std::endl;

			if(count == 10){
				obj_cpumem = &objSC;
				obj_cpumem->stopThread();

				obj_cpumem = &objSM;
				obj_cpumem->stopThread();
				break;
			}
		}
		sleep(1);
	}
	return 0;
}
