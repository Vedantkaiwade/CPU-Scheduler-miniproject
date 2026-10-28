#ifndef SORTING_H
#define SORTING_H

#include "Process.h"

void selectionSortByBurst(const ProcessTable& pt,int idx[],int n);

void quickSortByPriority(const ProcessTable& pt,int idx[],int low,int high);

void bubbleSortByPID(const ProcessTable& pt,int idx[],int n);

#endif
