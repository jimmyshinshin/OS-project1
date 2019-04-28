#define _GNU_SOURCE
/*
#define CPU_SETSIZE 1024
#define __NCPUBITS  (8 * sizeof (unsigned long))
typedef struct
{
   unsigned long __bits[CPU_SETSIZE / __NCPUBITS];
} cpu_set_t;
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "scheduler.h"
#include "process.h"

int checkPolicy(char *policy_name){
	if(strcmp(policy_name, "FIFO") == 0){
		return FIFO;	
	}else if(strcmp(policy_name, "RR") == 0){
		return RR;
	}else if(strcmp(policy_name, "SJF") == 0){
		return SJF;	
	}else if(strcmp(policy_name, "PSJF") == 0){
		return PSJF;	
	}else{
		fprintf(stderr, "Schedule Policy error, doesn't exist\n");
		exit(1);
	}

} 

void setCore(pid_t pid, int core){
	
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);

	if(sched_setaffinity(pid, sizeof(mask), &mask) < 0){
		fprintf(stderr, "setaffinity error\n");	
		exit(1);
	}
	return;
}


void Schedule(Process ps[], int num_procs, int policy){
	
	int running = -1;
	int my_time = 0;
	int last_switch;
	int remaining = num_procs;
	setCore(0, 0);
	psHigh(getpid());
	
	
	while(1){

		if(running != -1 && ps[running].E == 0){
			printf("%s %d\n", ps[running].name, ps[running].pid);
			fprintf(stderr,"Process finish, name = %s, pid = %d, time = %d\n", ps[running].name, ps[running].pid, my_time);
			waitpid(ps[running].pid, NULL, 0);
			running = -1;
			remaining -= 1;
			if(remaining == 0) break;
		}


		for(int i = 0; i < num_procs; i++){
			if(ps[i].R == my_time){
				ps[i].pid = psExec(ps[i]);
				psLow(ps[i].pid);
				fprintf(stderr, "Process start, name = %s, pid = %d, time = %d\n", ps[i].name, ps[i].pid, my_time);
			}	
		}

		int next = selectProcess(ps, num_procs, policy, running, my_time);
		
		if(next != -1){
			if(next != running){
				fprintf(stderr, "Context switch\n");
				psHigh(ps[next].pid);
				psLow(ps[running].pid);
				running = next;
				last_switch = my_time;
			}	
			
		}

		/* Run 1 unit time */
		volatile unsigned long i; for(i=0;i<1000000UL;i++);
		

		/* Executing time - 1 */
		if(running != -1)
			ps[running].E -= 1;

		my_time += 1;
	}

	return;
}
