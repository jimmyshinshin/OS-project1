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

int checkPolicy(char *policy_name) {
	if (!strcmp(policy_name, "FIFO")) {
		return FIFO;	
	} else if (!strcmp(policy_name, "RR")) {
		return RR;
	} else if (!strcmp(policy_name, "SJF")) {
		return SJF;	
	} else if (!strcmp(policy_name, "PSJF")) {
		return PSJF;	
	} else {
		fprintf(stderr, "Schedule Policy error, doesn't exist\n");
		exit(1);
	}
} 

void setCore(pid_t pid, int core) {
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);
	if(sched_setaffinity(pid, sizeof(mask), &mask) < 0) {
		fprintf(stderr, "setaffinity error\n");	
		exit(1);
	}
}


void schedule(Process ps[], int num_procs, int policy){
	
	int running = -1;
	int now_time = 0;
	int last_switch;
	int remaining = num_procs;
	setCore(getpid(), PARENT_CPU);
	set_high_priority(getpid());
	
	while(1) {
		if (running != -1 && ps[running].exec == 0) {
			printf("%s %d\n", ps[running].name, ps[running].pid);
			fprintf(stderr,"Process finish, name = %s, pid = %d, time = %d\n", ps[running].name, ps[running].pid, now_time);
			waitpid(ps[running].pid, NULL, 0);
			running = -1;
			remaining -= 1;
			if(remaining == 0) break;
		}
		for (int i = 0; i < num_procs; i++) {
			if (ps[i].ready == now_time) {
				ps[i].pid = psExec(ps[i]);
				set_low_priority(ps[i].pid);
				fprintf(stderr, "Process start, name = %s, pid = %d, time = %d\n", ps[i].name, ps[i].pid, now_time);
			}	
		}

		int next = next_process(ps, num_procs, policy, running, now_time, last_switch);
		if (next != -1) {
			if (next != running) {
				fprintf(stderr, "Context switch\n");
				set_high_priority(ps[next].pid);
				set_low_priority(ps[running].pid);
				running = next;
				last_switch = now_time;
			}	
		}
		/* Run 1 unit time */
		volatile unsigned long i;
		for(i = 0; i < 1000000UL; i++);

		/* Executing time - 1 */
		if (running != -1)
			ps[running].exec--;
		now_time++;
	}
}
