
#ifndef SORTING_H
#define SORTING_H

#include "Process.h"

// Selection Sort: sort process indices by burst time
void selectionSortByBurst(const ProcessTable& pt, int indices[], int n);

// Quick Sort: sort process indices by priority
void quickSortByPriority(const ProcessTable& pt, int indices[], int low, int high);

// Bubble Sort: sort process indices by PID
void bubbleSortByPID(const ProcessTable& pt, int indices[], int n);

#endif
