# Code Walkthrough: Multi-Core Round Robin Scheduler

## 1. The Problem We Are Solving

In modern operating systems, CPUs have multiple cores. When multiple programs (processes) want to run, the OS must decide **which process runs on which core, and for how long**. 

We are simulating a **Multi-Core Round Robin (RR) Scheduler** with **Dynamic Load Balancing**. 
Specifically, we are solving three main challenges:
1. **Fairness (Time-Slicing):** Ensuring no single process hogs a CPU core. We use the Round Robin algorithm where each process gets a small slice of time (Quantum).
2. **Initial Distribution:** When a new process arrives, which core should it go to? We solve this by placing it in the core with the fewest waiting processes.
3. **Dynamic Migration (Load Balancing):** What if one core finishes all its tasks quickly and becomes idle, while another core is backed up? We solve this by periodically checking the cores. If one core has at least 2 more processes than another, we "migrate" (move) a process from the busy core to the free core.

To make this a true Data Structures project, we **did not use built-in C++ queues** (like `std::queue`). Instead, we hand-built a **Circular Singly Linked List** from scratch to manage the waiting processes.

---

## 2. Data Structures Used

### The `Process` and `Node` Structs
* **`Process`**: Holds all data for a single job (PID, Arrival Time, Burst Time, Waiting Time, etc.).
* **`Node`**: A standard linked list node containing a `Process` and a pointer to the `next` node.

### The `CircularQueue` Class (OOP Encapsulation)
We used a **Circular Singly Linked List** because Round Robin scheduling operates in a circle (when a process's time is up, it goes to the back of the line). 
Instead of tracking both a `head` and a `tail`, we only track the `tail`. In a circular list, the head is simply `tail->next`.

We encapsulated this inside a class with exactly 3 methods:
1. **`push(Process p)`**: Adds a new process to the `tail` and links it back to the head. ($\mathcal{O}(1)$ time)
2. **`pop(bool fromTail)`**: 
   * **Default:** Removes the process at the `head` (when a process finishes). ($\mathcal{O}(1)$ time)
   * **Migration:** Removes the process at the `tail` (when we need to move a process to another core). ($\mathcal{O}(n)$ time)
3. **`front()`**: Returns a reference to the process currently at the `head` so the CPU can execute it. ($\mathcal{O}(1)$ time)

*Smart Trick:* To "rotate" a process in Round Robin (when its time slice expires), we simply do `push(pop())`. This removes it from the front and instantly puts it at the back!

---

## 3. The Core Simulation Engine (`runRoundRobin`)

This is where the magic happens. The `runRoundRobin` function loops through time, tick by tick (`currentTime++`), acting like the system clock. 

Inside the loop, it does 3 steps per tick:

**Step 1: Handle Arrivals**
If any processes arrive at the current time, we find the core with the lowest `processCount` and `push()` the process into that core's circular queue.

**Step 2: Execute Processes (The CPU)**
We loop through all $N$ cores. If a core has processes:
* We look at the `front()` process.
* We reduce its `remainingTime` by 1.
* **If it finishes (`remainingTime == 0`):** We `pop()` it permanently, calculate its Turnaround Time and Waiting Time, and save it to the completed list.
* **If its Time Quantum expires:** We reset its quantum timer and move it to the back using `push(pop())`.

**Step 3: Migration (Load Balancing)**
Every $K$ ticks (the rebalance interval), the system inspects all cores:
* It finds the `maxCore` (most busy) and `minCore` (least busy).
* If `maxCore` has $\ge 2$ more processes than `minCore`:
* It calls `pop(true)` on `maxCore` to grab the process at the tail, and `push()`es it into `minCore`.

---

## 4. The UI and Output (`printSummary` & `main`)

* **`printSummary`**: Takes the data from the simulation and creates clean visual outputs. It builds a text-based Gantt chart, dynamically maps PIDs to letters (e.g., A=P1, B=P2) for the timeline, and calculates averages (Average Waiting Time, CPU Utilization).
* **`main`**: A simple `while` loop providing an interactive terminal menu. It holds pre-configured scenarios (Option 1, 2, 3) designed to perfectly demonstrate single-core RR, process migration, and staggered arrivals, plus a custom input option.

## 5. Summary of Our Achievements
By writing this, we built a highly efficient simulation that demonstrates:
1. Mastery of pointers and manual memory management (Circular Linked Lists).
2. Clean Object-Oriented Programming (encapsulation of the Queue).
3. Operating System concepts (Context switching, Round Robin, CPU Load Balancing).
4. Code optimization (Keeping the whole architecture restricted to exactly 6 distinct functions).
