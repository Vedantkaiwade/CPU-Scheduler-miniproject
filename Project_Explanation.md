# CPU Scheduling Simulator — Complete File-by-File Code Explanation & Viva Guide

**Course:** Data Structures Laboratory (S.Y. B.Tech Computer Engineering, PICT Pune)  
**Project Title:** CPU Scheduling Simulator  
**Submitted By:** Kavin Sharma & Vedant Kaiwade  
**Guided By:** Dr. K. C. Waghmare  

---

## 1. Project Overview & Architecture

The **CPU Scheduling Simulator** models how an Operating System allocates CPU execution time to competing processes. The project is divided into **5 modular components** (headers `.h` and implementations `.cpp`) to separate data structures, sorting/searching logic, scheduling algorithms, and the user interface.

### Architectural Summary Table

| File Pair | Core Responsibility | Data Structures / Algorithms Included |
| :--- | :--- | :--- |
| **`Process.h` / `Process.cpp`** | Process storage and fast PID lookup | Fixed Array (`pro[50]`), Hash Table with Linear Probing (`hashTable[101]`), Linear Search, Binary Search |
| **`Sorting.h` / `Sorting.cpp`** | Ordering processes via index arrays without mutating the main table | Selection Sort (by Burst Time), Quick Sort (by Priority), Bubble Sort (by PID) |
| **`Structures.h` / `Structures.cpp`** | Custom dynamic linked data structures | Circular Singly Linked List, Double-Ended Queue (Deque), LIFO Stack, Binary Search Tree (BST), Doubly Linked List |
| **`Scheduler.h` / `Scheduler.cpp`** | CPU execution simulation, Gantt chart formatting, and metric calculation | FCFS, Non-Preemptive SJF, Non-Preemptive Priority, Preemptive Round Robin |
| **`main.cpp`** | Interactive command-line interface (CLI) | 12-option menu connecting all modules + sample workload loader |

---

## 2. Detailed File-by-File Explanation

---

### Module 1: `Process.h` and `Process.cpp`

#### Purpose
Stores every process's attributes (Process Control Block) and provides multiple ways to search for a process by its `pid`.

#### Key Data Structures
1. **`struct Process`**:
   - `pid`: Unique Process Identifier.
   - `at`: Arrival Time (when the process enters the ready state).
   - `bt`: Burst Time (total CPU time required).
   - `prio`: Priority value (convention: **lower number = higher priority**).
   - `remaining`: Remaining CPU burst time (used during preemptive Round Robin execution).
   - `ct`, `wt`, `tat`: Completion Time, Waiting Time, and Turnaround Time.

2. **`class ProcessTable`**:
   - **`Process pro[50]`**: Contiguous static array holding up to 50 processes in their exact insertion order.
   - **`int hashTable[101]`**: Open-addressing hash table storing the array index of each process.
     - **Hash Function:** `hashFunc(pid) = pid % 101`.
     - **Why 101?** `101` is a prime number greater than `2 * MAX` (`100`), which keeps the load factor below `0.5` and minimizes primary clustering during linear probing.
     - **Collision Resolution (Linear Probing):** If `hashTable[slot]` is occupied, it advances sequentially using `slot = (slot + 1) % 101` until an empty slot (`-1`) is found.

#### Key Functions
- **`addProcess(pid, at, bt, prio)`**: Validates inputs, checks for duplicate PIDs via `hashSearch(pid)`, appends the process to `pro[count]`, and inserts its index into `hashTable`.
- **`removeLast()`**: Decrements `count` and rebuilds the hash table. Called when popping from the Undo Stack.
- **`linearSearch(pid)`**: Scans `pro[0 ... count-1]` sequentially in $O(n)$ time.
- **`binarySearch(pid)`**: Creates a temporary index array `idx[]`, sorts `idx[]` by PID, and performs binary search in $O(\log n)$ time without altering the actual `pro[]` array.
- **`hashSearch(pid)`**: Computes `slot = pid % 101` and probes linearly to locate the process index in $O(1)$ average time.

---

### Module 2: `Sorting.h` and `Sorting.cpp`

#### Purpose
Sorts an **array of indices** (`int idx[]`) rather than swapping elements inside `ProcessTable`. This guarantees that the main table always preserves insertion order while allowing different parts of the program to view processes in sorted order.

#### Key Functions
1. **`selectionSortByBurst(pt, idx, n)`**:
   - **Algorithm:** Repeatedly scans the unsorted subarray to find the process index with the minimum `bt` (burst time) and swaps it to the front.
   - **Complexity:** $O(n^2)$ time, $O(1)$ auxiliary space.
   - **Where Used:** Called inside **SJF Scheduling** to pick the shortest available job among arrived processes, and in Menu Option 6.

2. **`quickSortByPriority(pt, idx, low, high)`** & **`partitionByPriority(...)`**:
   - **Algorithm:** Selects the last element's priority as the pivot (`pivotPrio`), partitions all indices with `prio <= pivotPrio` to the left, and recursively sorts both partitions.
   - **Complexity:** $O(n \log n)$ average time, $O(n^2)$ worst case.
   - **Where Used:** Called inside **Priority Scheduling** to select the highest-priority arrived process (lowest numerical priority value), and in Menu Option 6.

3. **`bubbleSortByPID(pt, idx, n)`**:
   - **Algorithm:** Compares adjacent indices (`idx[j]` and `idx[j+1]`) by `pid` and swaps them if out of order. Uses a `bool swapped` flag to terminate early in $O(n)$ if already sorted.
   - **Complexity:** $O(n^2)$ worst/average, $O(n)$ best.
   - **Where Used:** Called before printing the final scheduling metrics table so results always appear neatly ordered by `PID`.

---

### Module 3: `Structures.h` and `Structures.cpp`

#### Purpose
Implements 5 custom pointer-based data structures from scratch without C++ STL containers (`std::queue`, `std::list`, `std::stack`, etc.).

#### The 5 Data Structures

1. **Circular Singly Linked List (`class CircularQueue`)**:
   - **Pointer Design:** Maintains a single `CircularNode* tail` pointer where `tail->next` always points to the front (head) node.
   - **Why Only `tail`?** Maintaining `tail` gives $O(1)$ access to both the back (`tail`) and the front (`tail->next`) without needing two separate pointers.
   - **Operations:**
     - `enqueue(idx)`: Inserts a new node after `tail` and updates `tail = n` in $O(1)$ time.
     - `dequeue()`: Removes `tail->next` and returns its process index in $O(1)$ time.
   - **Role:** Ready queue for **Round Robin** scheduling.

2. **Double-Ended Queue (`class ProcessDeque`)**:
   - **Pointer Design:** Doubly linked nodes (`next`, `prev`) with `front` and `rear` pointers.
   - **Operations:**
     - `addRear(idx)`: Normal process admission at the back ($O(1)$).
     - `addFront(idx)`: **Urgent process admission** directly at the front of the line ($O(1)$).
     - `removeFront()`: Removes from the front ($O(1)$).
   - **Role:** Demonstrates normal vs. urgent process admission in Menu Options 1, 2, and 4.

3. **LIFO Stack (`class UndoStack`)**:
   - **Pointer Design:** Singly linked list with `StackNode* top`.
   - **Operations:** `push(pid)` and `pop()` in $O(1)$ time.
   - **Role:** Records added PIDs so Menu Option 3 can undo the most recent process addition.

4. **Binary Search Tree (`class ProcessBST`)**:
   - **Pointer Design:** Tree nodes (`pid`, `left`, `right`) satisfying the BST property: `left->pid < node->pid < right->pid`.
   - **Operations:**
     - `insert(pid)`: Recursive insertion in $O(\log n)$ average time.
     - `search(pid)`: Recursive lookup in $O(\log n)$ average time.
     - `displayInorder()`: Left-Root-Right recursive traversal that prints all PIDs in ascending sorted order in $O(n)$ time.
   - **Role:** Acts as an indexed Process Directory in Menu Options 4 and 5.

5. **Doubly Linked List (`class RunHistory`)**:
   - **Pointer Design:** Nodes storing `policy`, `avgWT`, `avgTAT`, and the 2-line `gantt` string, linked via `prev` and `next` pointers (`head`, `tail`, `current`).
   - **Operations:**
     - `addRun(...)`: Appends a completed simulation run at `tail` and sets `current = tail`.
     - `movePrev()` / `moveNext()`: Moves the `current` cursor backward or forward in $O(1)$ time.
   - **Role:** Stores execution history across multiple scheduling runs so you can compare policies in Menu Option 11.

---

### Module 4: `Scheduler.h` and `Scheduler.cpp`

#### Purpose
Contains the 4 CPU scheduling policies, idle-time gap handling, Gantt chart generator, and turnaround/waiting time calculations.

#### Core Formulas
- $\text{Turnaround Time (TAT)} = \text{Completion Time (CT)} - \text{Arrival Time (AT)}$
- $\text{Waiting Time (WT)} = \text{Turnaround Time (TAT)} - \text{Burst Time (BT)}$

#### Helper Functions
- **`resetProcessMetrics(pt)`**: Resets `remaining = bt` and zeroes out `ct`, `wt`, and `tat` before every simulation run so multiple algorithms can be run back-to-back on the same dataset.
- **`printGanttAndResults(...)`**:
  - Builds the two-line ASCII Gantt chart:
    ```text
    | P1 | P2 | P3 | P4 |
    0    7   11   12   16
    ```
  - Uses `bubbleSortByPID` to print the per-process table sorted by PID.
  - Calculates average Waiting Time and Turnaround Time and saves the run into `RunHistory`.

#### The 4 Scheduling Algorithms

1. **`runFCFS(pt, history)` — First-Come, First-Served**:
   - Sorts an index array `order[]` by Arrival Time (`at`).
   - Iterates through `order[]`. If `curTime < p.at`, records a CPU `IDLE` block (`pid = -1`) from `curTime` to `p.at` and jumps `curTime = p.at`.
   - Executes each process completely (`curTime += p.bt`) and records `ct`, `tat`, and `wt`.

2. **`runSJF(pt, history)` — Shortest Job First (Non-Preemptive)**:
   - Tracks `bool done[]` and `finished` count.
   - At `curTime`, collects all unfinished processes with `at <= curTime` into `ready[]`.
   - If `rCount == 0` (no process has arrived yet), jumps `curTime` to the earliest `at` among remaining processes and logs an `IDLE` block.
   - Calls **`selectionSortByBurst(pt, ready, rCount)`** so `ready[0]` holds the shortest burst job.
   - Runs `ready[0]` to completion and marks `done[pick] = true`.

3. **`runPriority(pt, history)` — Priority Scheduling (Non-Preemptive)**:
   - Collects all unfinished processes with `at <= curTime` into `ready[]` (jumping across idle gaps if `rCount == 0`).
   - Calls **`quickSortByPriority(pt, ready, 0, rCount - 1)`** so `ready[0]` holds the process with the lowest priority number (highest priority).
   - Runs `ready[0]` to completion.

4. **`runRoundRobin(pt, timeQuantum, history)` — Round Robin (Preemptive)**:
   - Sorts `order[]` by arrival time and initializes `CircularQueue queue`.
   - Enqueues all processes arriving at the initial timestamp.
   - In a loop until `finished == n`:
     - Dequeues front process `curr` from `CircularQueue`.
     - Executes it for `slice = min(p.remaining, timeQuantum)` and advances `curTime += slice`.
     - Merges consecutive Gantt blocks if the same process ran back-to-back.
     - **Crucial Rule:** Enqueues any newly arrived processes (`at <= curTime`) into `CircularQueue` *before* re-enqueuing the current process.
     - If `p.remaining == 0`, computes `ct`, `tat`, `wt`, and increments `finished`. Otherwise, rotates `curr` to the back via `queue.enqueue(curr)`.

---

### Module 5: `main.cpp`

#### Purpose
Ties all modules together into an interactive 12-option command-line menu:
- **Option 1 (Add Process):** Inserts into `ProcessTable` (Array + Hash Table), `ProcessDeque` (rear), `UndoStack`, and `ProcessBST`.
- **Option 2 (Add Urgent Process):** Inserts at the **front** of `ProcessDeque` (`addFront`).
- **Option 3 (Undo):** Pops last PID from `UndoStack` and removes it from `ProcessTable`.
- **Option 4 (Display):** Prints the Process Table, Admission Deque order, and BST Inorder traversal.
- **Option 5 (Search):** Runs Linear, Binary, Hash, and BST searches simultaneously for any PID.
- **Option 6 (Sort):** Runs Selection (Burst), Quick (Priority), or Bubble (PID) sort and displays the resulting order.
- **Options 7–10:** Executes FCFS, SJF, Priority, and Round Robin.
- **Option 11 (History):** Navigates backward and forward through completed runs using the Doubly Linked List.
- **Option 12 (Load Sample Workload):** Auto-loads 4 test processes (`P1`–`P4`) for instant viva demonstration.

---

## 3. Complexity Cheat Sheet for Viva

| Operation / Structure | Average Time Complexity | Worst-Case Time Complexity | Where Used in Project |
| :--- | :---: | :---: | :--- |
| **Linear Search** | $O(n)$ | $O(n)$ | `ProcessTable::linearSearch` |
| **Binary Search** | $O(\log n)$ | $O(\log n)$ | `ProcessTable::binarySearch` |
| **Hash Table Lookup** | $O(1)$ | $O(n)$ | `ProcessTable::hashSearch` |
| **BST Insert / Search** | $O(\log n)$ | $O(n)$ (skewed) | `ProcessBST::insert` / `search` |
| **Circular Queue Enqueue/Dequeue** | $O(1)$ | $O(1)$ | Round Robin Ready Queue |
| **Deque Add Front / Rear** | $O(1)$ | $O(1)$ | Normal & Urgent Process Admission |
| **Stack Push / Pop** | $O(1)$ | $O(1)$ | Undo Last Process Addition |
| **Doubly Linked List Prev / Next** | $O(1)$ | $O(1)$ | Run History Navigation |
| **Selection Sort** | $O(n^2)$ | $O(n^2)$ | SJF Burst Time Sorting |
| **Bubble Sort** | $O(n^2)$ | $O(n^2)$ | PID Table Sorting ($O(n)$ best case) |
| **Quick Sort** | $O(n \log n)$ | $O(n^2)$ | Priority Scheduling Sorting |
