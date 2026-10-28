# Multi-Core Round Robin Scheduler Simulator

A clean, streamlined C++ console simulator for **Round Robin CPU scheduling across N cores** using hand-built linked lists (no STL queue/deque/list).

---

## Data Structures

```cpp
struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime = -1;
    int waitingTime = 0;
    int turnaroundTime = 0;
    int coreId = -1;
    int migrations = 0;
};

struct Node {
    Process data;
    Node* next;
};

struct CoreQueue {
    int coreId;
    Node* tail = nullptr; // Circular list: tail->next == head
    int quantum;
    int currentLoad = 0;  // Sum of remainingTime across all processes
    int busyTime = 0;     // Ticks core was busy
    int quantumUsed = 0;  // Ticks in current quantum slice
};

struct IncomingQueue {
    Node* head = nullptr; // Linear list sorted by arrivalTime
};
```

---

## 6-Task Implementation Breakdown

1. **Task 1 — CoreQueue Circular List Mechanics**:
   - `enqueueCore(cq, p)`: Insert at tail ($\mathcal{O}(1)$).
   - `peekHeadCore(cq)`: Access running process ($\mathcal{O}(1)$).
   - `removeHeadCore(cq)`: Delete head node upon process completion ($\mathcal{O}(1)$).
   - `rotateCore(cq)`: Advance tail on quantum expiration ($\mathcal{O}(1)$ with zero heap allocations).
   - `removeTailCore(cq)`: Unlink tail node for migration ($\mathcal{O}(n)$).
2. **Task 2 — Single-Core RR Loop**:
   - Run $N=1$ Round Robin with time quantum $Q$.
3. **Task 3 — Incoming Linear Queue & Multi-Core**:
   - `insertIncoming(iq, p)`: Sorted insertion by `arrivalTime`.
   - `popArrived(iq, currentTime)`: Dequeues arrivals at each simulation tick.
4. **Task 4 — Load Balancing**:
   - Assign newly arrived processes to the core with minimum `currentLoad` (ties broken by lowest `coreId`).
5. **Task 5 — Dynamic Migration**:
   - Every `rebalanceInterval` ticks: compute `imbalance = maxLoad - minLoad`.
   - If `imbalance > threshold`: remove process from tail of most-loaded core and insert at tail of least-loaded core.
6. **Task 6 — Output, Metrics & Menu**:
   - Per-core Gantt charts & ASCII timeline.
   - Summary table ($PID, Arr, Burst, CT, TAT, WT, Migrations, Core$).
   - Per-core utilization % ($busyTime / totalTime$).
   - Average Waiting Time & Average Turnaround Time.

---

## Menu Options

```
==================================================
   Multi-Core Round Robin Scheduler Simulator     
==================================================
  [1] Single-Core Round Robin (N=1)
  [2] Multi-Core with Migration Demo
  [3] Staggered Arrivals, No Migration
  [4] Custom Workload Input
  [0] Exit
--------------------------------------------------
```

---

## Build & Run

```bash
# Compile
g++ -std=c++17 -Wall -Wextra -O2 -o scheduler.exe scheduler.cpp

# Run
./scheduler.exe
```
