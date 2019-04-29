/* Only main function */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h> 
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include "process.h"
#include "scheduler.h"


int main(int argc, char **argv){
	char policy_name[64];
	int n_proc;
	
	scanf("%s%d", policy_name, &n_proc);

	int policy = checkPolicy(policy_name);
	Process *p = (Process*)malloc(sizeof(Process)*n_proc);

	for (int i = 0; i < n_proc; i++) {	
		scanf("%s%u%u", p[i].name, &p[i].ready, &p[i].exec);
		p[i].pid = -1;
	}
	schedule(p, n_proc, policy);
	return 0;
}
