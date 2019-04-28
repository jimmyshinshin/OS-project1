/* Only main function */
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include "process.h"
#include "scheduler.h"


int main(int argc, char **argv){

	char policy_name[64];
	int num_procs;

	scanf("%s%d", policy_name, &num_procs);
	
	int policy = checkPolicy(policy_name);

	Process ps[num_procs];
	for(int i = 0; i < num_procs; i++){	
		scanf("%s %u %u", ps[i].name, &ps[i].R, &ps[i].E);
		ps[i].pid = -1;
	}

	Schedule(ps, num_procs, policy);
	return 0;
	

}
