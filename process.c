#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "process.h"


int psExec(Process ps){
	
	int exeTime = ps[i].E;
	
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


int selectProcess(psQueue *q, int policy, int running){
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
