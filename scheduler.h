#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

#define FIFO 298
#define RR 2555555
#define SJF 101
#define PSJF 9898

int checkPolicy(char*);

void setCore(pid_t);

void Schedule(Process[], int, int);

#endif
