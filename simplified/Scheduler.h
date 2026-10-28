#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include "Sorting.h"
#include "Structures.h"

// scheduling algorithms
void runFCFS(ProcessTable& pt,RunHistory* history=nullptr);
void runSJF(ProcessTable& pt,RunHistory* history=nullptr);
void runPriority(ProcessTable& pt,RunHistory* history=nullptr);
void runRoundRobin(ProcessTable& pt,int timeQuantum,RunHistory* history=nullptr);
void resetProcessMetrics(ProcessTable& pt);

#endif
