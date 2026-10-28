# Multi-Core Round Robin CPU Scheduler Simulator — Project Summary

### 📌 Overview
A lightweight C++ console application simulating **Round Robin CPU scheduling across $N$ cores**. The simulation executes multiple cores in lockstep time ticks without real OS threads or STL queue containers, using an encapsulated, hand-built **Circular Singly Linked List**.

---

### 🏗️ Architecture & Data Structures (OOP)
- **`CircularQueue` Class**: Encapsulates each CPU core's ready queue via a private `tail` pointer (`tail->next == head`).
- **Encapsulated Methods**:
  - `push(Process p)`: Inserts at tail ($\mathcal{O}(1)$).
  - `pop(bool fromTail)`: Dequeues head ($\mathcal{O}(1)$) or unlinks tail for migration ($\mathcal{O}(n)$).
  - `front()`: Accesses the active running process at head ($\mathcal{O}(1)$).

---

### ⚙️ Core Scheduling Logic
1. **Load Balancer on Arrival**: Arriving processes are assigned to the core with the **fewest active processes** (`processCount`).
2. **Per-Core Round Robin**: Each core executes its front process for 1 tick per loop. On quantum expiration, the process is rotated to the back via `push(pop(false))`.
3. **Dynamic Process Migration**: Every $K$ ticks, if $(\text{maxProcesses} - \text{minProcesses} \ge 2)$, **ONE** process is migrated from the busiest core's tail to the lightest core's tail.
4. **Performance Formulas**:
   $$\text{Turnaround Time (TAT)} = \text{Completion Time} - \text{Arrival Time}$$
   $$\text{Waiting Time (WT)} = \text{Turnaround Time} - \text{Burst Time}$$
   $$\text{Core Utilization \%} = \frac{\text{Core Busy Ticks}}{\text{Total Simulation Ticks}} \times 100\%$$

---

### 🧩 6-Function Code Breakdown
The entire codebase consists of **exactly 6 functions**:
1. `CircularQueue::push(Process p)` — Enqueue at tail.
2. `CircularQueue::pop(bool fromTail)` — Dequeue head / tail.
3. `CircularQueue::front()` — Access head process.
4. `runRoundRobin(...)` — Main multi-core lockstep simulation engine.
5. `printSummary(...)` — Formats Gantt chart, timeline, sorted table, and metrics.
6. `main()` — Interactive menu loop with preset scenarios and custom input.

---

### 📊 Program Outputs
- **Per-Core Gantt Chart**: Start and end time ranges for each process slice and idle period.
- **Dynamic Character Timeline**: Auto-mapped process letters (`A=P1, B=P2, ...`).
- **Process Summary Table**: PID, Arrival, Burst, Completion, Turnaround, Waiting, Final Core.
- **Performance Metrics**: Per-core utilization %, total migrations, average waiting time, average turnaround time.

---

### 🚀 Compilation & Execution
**Local Path**: `C:\Users\Kavin\Desktop\CIE_DSA_PROJECT\`

```bash
# Compile
g++ -std=c++17 -Wall -Wextra -O2 -o scheduler.exe scheduler.cpp

# Run
./scheduler.exe
```
