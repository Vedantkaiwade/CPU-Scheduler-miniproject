#include <iostream>
#include "Scheduler.h"

using namespace std;

int main() {
    cout << "======================================================\n";
    cout << "       Testing Module 4: CPU Scheduler Simulator       \n";
    cout << "======================================================\n";

    // Setup ProcessTable with 4 sample processes
    ProcessTable pt(4);
    pt.addProcess(1, 0, 7, 3); // PID 1, Arr 0, Burst 7, Prio 3
    pt.addProcess(2, 2, 4, 1); // PID 2, Arr 2, Burst 4, Prio 1
    pt.addProcess(3, 4, 1, 4); // PID 3, Arr 4, Burst 1, Prio 4
    pt.addProcess(4, 5, 4, 2); // PID 4, Arr 5, Burst 4, Prio 2

    cout << "\nInitial Processes in Table:\n";
    pt.displayAll();

    SchedulerHistory history;

    // 1. Run First-Come, First-Served (FCFS)
    cout << "\n\n>>> Running Policy 1: FCFS";
    runFCFS(pt, &history);

    // 2. Run Shortest Job First (SJF)
    cout << "\n\n>>> Running Policy 2: SJF (Non-preemptive)";
    runSJF(pt, &history);

    // 3. Run Priority Scheduling
    cout << "\n\n>>> Running Policy 3: Priority (Non-preemptive)";
    runPriority(pt, &history);

    // 4. Run Round Robin (Quantum = 2)
    cout << "\n\n>>> Running Policy 4: Round Robin (Q = 2)";
    runRoundRobin(pt, 2, &history);

    // 5. Test Run History Doubly Linked List Navigation
    cout << "\n\n======================================================\n";
    cout << "        Testing Run History Doubly Linked List        \n";
    cout << "======================================================\n";

    history.displayAll();

    cout << "\nCurrent selection after all runs:\n";
    history.displayCurrent();

    cout << "\nMoving backward in history (should show Priority):\n";
    if (history.movePrevious()) {
        history.displayCurrent();
    }

    cout << "\nMoving backward again (should show SJF):\n";
    if (history.movePrevious()) {
        history.displayCurrent();
    }

    cout << "\nMoving forward (should return to Priority):\n";
    if (history.moveNext()) {
        history.displayCurrent();
    }

    cout << "\nAll Scheduler tests completed successfully!\n";
    return 0;
}
