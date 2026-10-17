
#include "Sorting.h"

// ------------------------------------
// 1. SELECTION SORT BY BURST TIME
// ------------------------------------
void selectionSortByBurst(const ProcessTable& pt,
                          int indices[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            int currentBurst =
                pt.getProcess(indices[j]).burst_time;

            int minBurst =
                pt.getProcess(indices[minIndex]).burst_time;

            if (currentBurst < minBurst) {
                minIndex = j;
            }
        }

        int temp = indices[i];
        indices[i] = indices[minIndex];
        indices[minIndex] = temp;
    }
}

// ------------------------------------
// 2. QUICK SORT BY PRIORITY
// Lower number = higher priority
// ------------------------------------
int partitionByPriority(const ProcessTable& pt,
                        int indices[], int low, int high) {
    int pivotPriority =
        pt.getProcess(indices[high]).priority;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (pt.getProcess(indices[j]).priority <= pivotPriority) {
            i++;

            int temp = indices[i];
            indices[i] = indices[j];
            indices[j] = temp;
        }
    }

    int temp = indices[i + 1];
    indices[i + 1] = indices[high];
    indices[high] = temp;

    return i + 1;
}

void quickSortByPriority(const ProcessTable& pt,
                         int indices[], int low, int high) {
    if (low < high) {
        int pivot = partitionByPriority(pt, indices, low, high);

        quickSortByPriority(pt, indices, low, pivot - 1);
        quickSortByPriority(pt, indices, pivot + 1, high);
    }
}

// ------------------------------------
// 3. BUBBLE SORT BY PID
// ------------------------------------
void bubbleSortByPID(const ProcessTable& pt,
                     int indices[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            int pid1 = pt.getProcess(indices[j]).pid;
            int pid2 = pt.getProcess(indices[j + 1]).pid;

            if (pid1 > pid2) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;

                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}
