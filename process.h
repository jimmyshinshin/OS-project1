#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCS 65536
typedef struct process{
	char name[64];
	unsigned int R;
	unsigned int E;
	int pid;
} Process;



int selectProcess(Process ps[], int policy);
#endif
