
#include <iostream>
#include "Sorting.h"
using namespace std;

void displayOrder(const ProcessTable& pt, int indices[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "P" << pt.getProcess(indices[i]).pid << " ";
    }
    cout << "\n";
}

int main() {
    ProcessTable pt(3);

    pt.addProcess(1, 0, 7, 2);
    pt.addProcess(2, 1, 3, 1);
    pt.addProcess(3, 2, 5, 3);

    int n = pt.getCount();
    int indices[3];

    // Test selection sort by burst time
    for (int i = 0; i < n; i++) indices[i] = i;

    selectionSortByBurst(pt, indices, n);
    cout << "Selection sort by burst time: ";
    displayOrder(pt, indices, n);

    // Test quick sort by priority
    for (int i = 0; i < n; i++) indices[i] = i;

    quickSortByPriority(pt, indices, 0, n - 1);
    cout << "Quick sort by priority: ";
    displayOrder(pt, indices, n);

    // Test bubble sort by PID
    for (int i = 0; i < n; i++) indices[i] = i;

    bubbleSortByPID(pt, indices, n);
    cout << "Bubble sort by PID: ";
    displayOrder(pt, indices, n);

    return 0;
}
