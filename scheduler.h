#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

#define FIFO 1
#define RR 2
#define SJF 3
#define PSJF 4

int checkPolicy(char*);

void setCore(pid_t, int);

void schedule(Process[], int, int);

#endif
