#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include "process.h"
#include "scheduler.h"
#include <sched.h>
#include <sys/syscall.h>

int psExec(Process ps){
	int pid = fork();
	if (pid < 0){
		fprintf(stderr, "psExec error\n");
		exit(1);
	}
	if (pid == 0){ // Child Process
		unsigned long startsec, startnsec;
		syscall(333, &startsec, &startnsec);
		for(int i = 0; i < ps.exec; i++){
			volatile unsigned long j; 
			for(j = 0; j < 1000000UL; j++);	
		}
		unsigned long finishsec, finishnsec;
		syscall(333, &finishsec, &finishnsec);
		char message[512];
		sprintf(message, "[project1] %d %lu.%09lu %lu.%09lu\n", getpid(), startsec, startnsec, finishsec, finishnsec);
		syscall(334, message);
		exit(0);
	}
	setCore(pid, CHILD_CPU);
	return pid;
}

int set_high_priority(int pid){
	struct sched_param param;
	param.sched_priority = 0;
	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
	if (ret < 0) {
		perror("sched_setscheduler error\n");
		exit(1);
	}
	return ret;
}

int set_low_priority(int pid){
	struct sched_param param;
	param.sched_priority = 0;
	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler error\n");
		exit(1);
	}
	return ret;		
}

int next_process(Process ps[], int num_procs, int policy, int running, int now_time, int last_switch) {
	/* Different policies */
	int next = -1;
	if (policy == FIFO) {
		if (running != -1) 
			return running; // FIFO is non-preemtive
		for (int i = 0; i < num_procs; i++) {
			if(ps[i].exec == 0 || ps[i].pid == -1)	
				continue;
			if(next == -1 || ps[i].ready < ps[next].ready)
				next = i;	
		}
	} else if (policy == RR) {
		if (running == -1) {
			for (int i = 0; i < num_procs; i++) 
				if (ps[i].pid != -1 && ps[i].exec > 0) {
					return i;
			}
		} else if ((now_time-last_switch) % 500 == 0) {
			next = (running+1) % num_procs;
			while (ps[next].pid == -1 || ps[next].exec == 0) 
				next = (next+1) % num_procs;
		} else {
			next = running;
		}
	} else if (policy == SJF) {
		if (running != -1) 
			return running; // SJF is non-preemtive
		for (int i = 0; i < num_procs; i++) {
			if (ps[i].exec == 0 || ps[i].pid == -1)	
				continue;
			if (next == -1 || ps[i].exec < ps[next].exec)
				next = i;	
		}
	} else if (policy == PSJF) {
		for (int i = 0; i < num_procs; i++) {
			if (ps[i].exec == 0 || ps[i].pid == -1)	
				continue;
			if (next == -1 || ps[i].exec < ps[next].exec)
				next = i;	
		}
	}
	return next;
}
