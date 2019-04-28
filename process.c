#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include "process.h"
#include "scheduler.h"
#include <sched.h>


#define PRINTK 103
#define GET_TIME 228

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
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
	
	if (ret < 0) {
		fprintf(stderr, "sched_setscheduler error\n");
		exit(1);
	}

	return ret;

}

int psLow(int pid){

	struct sched_param param;
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
	
	if (ret < 0) {
		fprintf(stderr, "sched_setscheduler error\n");
		exit(1);
	}

	return ret;		
	
}
int selectProcess(Process ps[], int num_procs, int policy, int running, int last_switch){
	
	/* Different policies */
	if(policy == FIFO){

		if(running != -1) return running; // FIFO is non-preemtive
		
		int first = -1;
		for(int i = 1; i < num_procs; i++){
			if(ps[i].E == 0 || ps[i].pid == -1)	
				continue;
			if(first == -1 || ps[i].E < ps[first].E)
				first = i;	
		}

		return first;
		
	}else if(policy == RR){
		
		return running;
	
	}else if(policy == SJF){

		if(running != -1) return running; // SJF is non-preemtive
		
		int min = -1;
		for(int i = 1; i < num_procs; i++){
			if(ps[i].E == 0 || ps[i].pid == -1)	
				continue;
			if(min == -1 || ps[i].E < ps[min].E)
				min = i;	
		}

		return min;

	}else if(policy == PSJF){
		
		int min = -1;
		for(int i = 1; i < num_procs; i++){
			if(ps[i].E == 0 || ps[i].pid == -1)	
				continue;
			if(min == -1 || ps[i].E < ps[min].E)
				min = i;	
		}

		return min;
	}
	
	
	
}
