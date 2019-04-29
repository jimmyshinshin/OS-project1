#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCS 65536

typedef struct process{
	char name[64];
	unsigned int ready;
	unsigned int exec;
	pid_t pid;
} Process;

int psExec(Process);

int set_low_priority(int);

int set_high_priority(int);

int next_process(Process[], int, int, int, int);

#endif
