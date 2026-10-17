
#include "process.h"
#include <stdexcept>

// Constructor
ProcessTable::ProcessTable(int cap) {
    capacity = (cap > 0) ? cap : 0;
    count = 0;

    table = (capacity > 0) ? new Process[capacity] : nullptr;

    hashTableSize = (capacity * 2) + 1;
    hashTable = new int[hashTableSize];

    for (int i = 0; i < hashTableSize; i++) {
        hashTable[i] = -1;
    }
}

// Destructor
ProcessTable::~ProcessTable() {
    delete[] table;
    delete[] hashTable;
}

// Hash function
int ProcessTable::hashFunction(int pid) const {
    return pid % hashTableSize;
}

// Insert PID into hash table using linear probing
void ProcessTable::hashInsert(int pid, int index) {
    int slot = hashFunction(pid);
    int probes = 0;

    while (hashTable[slot] != -1 && probes < hashTableSize) {
        slot = (slot + 1) % hashTableSize;
        probes++;
    }

    if (probes < hashTableSize) {
        hashTable[slot] = index;
    }
}

// Add a process
bool ProcessTable::addProcess(int pid, int arrival_time,
                              int burst_time, int priority) {
    if (count >= capacity)
        return false;

    if (pid < 0 || arrival_time < 0 || burst_time <= 0)
        return false;

    if (hashSearchByPID(pid) != -1)
        return false;

    table[count].pid = pid;
    table[count].arrival_time = arrival_time;
    table[count].burst_time = burst_time;
    table[count].priority = priority;

    table[count].remaining_time = burst_time;
    table[count].completion_time = 0;
    table[count].waiting_time = 0;
    table[count].turnaround_time = 0;

    hashInsert(pid, count);
    count++;

    return true;
}

// Get number of processes
int ProcessTable::getCount() const {
    return count;
}

// Get process by index
Process& ProcessTable::getProcess(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Invalid process index");
    }

    return table[index];
}

const Process& ProcessTable::getProcess(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Invalid process index");
    }

    return table[index];
}

// Get the process array
const Process* ProcessTable::getProcessArray() const {
    return table;
}

// Linear search
int ProcessTable::linearSearchByPID(int pid) const {
    for (int i = 0; i < count; i++) {
        if (table[i].pid == pid) {
            return i;
        }
    }

    return -1;
}

// Binary search
int ProcessTable::binarySearchByPID(int pid) const {
    int* sortedIndex = new int[count];

    for (int i = 0; i < count; i++) {
        sortedIndex[i] = i;
    }

    // Sort indices by PID, leaving the original table unchanged
    for (int i = 1; i < count; i++) {
        int key = sortedIndex[i];
        int j = i - 1;

        while (j >= 0 &&
               table[sortedIndex[j]].pid > table[key].pid) {
            sortedIndex[j + 1] = sortedIndex[j];
            j--;
        }

        sortedIndex[j + 1] = key;
    }

    int low = 0;
    int high = count - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int index = sortedIndex[mid];

        if (table[index].pid == pid) {
            result = index;
            break;
        }
        else if (table[index].pid < pid) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    delete[] sortedIndex;
    return result;
}

// Hash search
int ProcessTable::hashSearchByPID(int pid) const {
    if (pid < 0)
        return -1;

    int slot = hashFunction(pid);
    int probes = 0;

    while (probes < hashTableSize) {
        int index = hashTable[slot];

        if (index == -1)
            return -1;

        if (table[index].pid == pid)
            return index;

        slot = (slot + 1) % hashTableSize;
        probes++;
    }

    return -1;
}

// Display all processes
void ProcessTable::displayAll() const {
    cout << "\nPID\tArrival\tBurst\tPriority\n";

    for (int i = 0; i < count; i++) {
        cout << table[i].pid << "\t"
             << table[i].arrival_time << "\t"
             << table[i].burst_time << "\t"
             << table[i].priority << "\n";
    }
}
