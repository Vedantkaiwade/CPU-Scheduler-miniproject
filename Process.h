#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
using namespace std;

// process structure
struct Process{
    int pid;
    int at;
    int bt;
    int prio;
    int remaining;
    int ct;
    int wt;
    int tat;
};

// process table using array and hash table
class ProcessTable{
private:
    static const int MAX=50;
    Process pro[MAX];
    int count;
    int hashTable[101];

    int hashFunc(int pid) const;

public:
    ProcessTable();
    bool addProcess(int pid,int at,int bt,int prio);
    bool removeLast();
    int getCount() const;
    Process& getProcess(int index);
    const Process& getProcess(int index) const;

    int linearSearch(int pid) const;
    int binarySearch(int pid) const;
    int hashSearch(int pid) const;
    void display() const;
};

#endif
