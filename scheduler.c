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

void setCore(pid_t pid){
	
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(0, &mask);

	if(sched_setaffinity(pid, sizeof(mask), &mask) < 0){
		fprintf(stderr, "setaffinity error\n");	
		exit(1);
	}
	return;
}
void Schedule(Process ps[], int num_procs, int policy){
	
	int running = -1;
	int my_time = 0;
	set_core(getpid());
	
	
	while(1){
/*
		if(running != -1 && ps[running].E == 0){
			
			
			
			
		}
*/

		for(int i = 0; i < num_procs; i++){
			if(ps[i].R == mytime){
				ps[i].pid = psExec(ps[i]);
			}	
			
			
		}


		

		/* Run 1 unit time */
		volatile unsigned long i; for(i=0;i<1000000UL;i++);
		
		/* Ready time - 1 */
		for(int i = 0; i < num_procs; i++)
			ps[i].R -= 1;

		/* Executing time - 1 */
		if(running != -1)
			ps[running].E -= 1;
	}
}
