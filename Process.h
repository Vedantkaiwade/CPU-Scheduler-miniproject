
#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;

    int completion_time;
    int waiting_time;
    int turnaround_time;
};

class ProcessTable {
private:
    Process* table;
    int count;
    int capacity;

    int* hashTable;
    int hashTableSize;

    int hashFunction(int pid) const;
    void hashInsert(int pid, int index);

public:
    explicit ProcessTable(int cap);
    ~ProcessTable();

    ProcessTable(const ProcessTable&) = delete;
    ProcessTable& operator=(const ProcessTable&) = delete;

    bool addProcess(int pid, int arrival_time,
                    int burst_time, int priority);

    int getCount() const;

    Process& getProcess(int index);
    const Process& getProcess(int index) const;
    
    const Process* getProcessArray() const;

    int linearSearchByPID(int pid) const;
    int binarySearchByPID(int pid) const;
    int hashSearchByPID(int pid) const;

    void displayAll() const;
};

#endif
