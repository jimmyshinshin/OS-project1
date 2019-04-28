#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include "process.h"
#include "scheduler.h"


int psExec(Process ps){
	
	int exeTime = ps.E;
	
	int pid = fork();

	if(pid < 0){
		fprintf(stderr, "psExec error\n");
		exit(1);
	}

	if(pid == 0){ // Child Process
		for(int i = 0; i < exeTime; i++){
			volatile unsigned long i; for(i=0;i<1000000UL;i++);	
		}	
		
		exit(0);
	}
	else
		return pid;
}

int psHigh(int pid){

	struct sched_param param;
	
	/* SCHED_OTHER should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler");
		return -1;
	}

	return ret;

}

int psLow(int pid){

	struct sched_param param;
	
	/* SCHED_IDLE should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler");
		return -1;
	}

	return ret;		
	
}
int selectProcess(Process ps[], int num_procs, int policy){
	/* If NO process is executing, return -1 */
	if(running == -1)
		return -1;
	
	/* Different policies */
	if(policy == FIFO){

		return running;

	}else if(policy == RR){
		

	
	}else if(policy == SJF){
		
		return running;

	}else if(policy == PSJF){
		
	}
	
	
	
}
