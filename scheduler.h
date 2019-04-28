#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

#define FIFO 298
#define RR 2555555
#define SJF 101
#define PSJF 9898

int checkPolicy(char *policy_name);

void setCore(pid_t pid);

void Schedule(Process ps[], int num_procs, int policy);

#endif
