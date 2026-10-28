#include "Process.h"

// initialize table and hash table
ProcessTable::ProcessTable(){
    count=0;
    for(int i=0;i<101;i++) hashTable[i]=-1;
}

// hash function based on PID
int ProcessTable::hashFunc(int pid) const{
    return pid%101;
}

// add process and insert into hash table with linear probing
bool ProcessTable::addProcess(int pid,int at,int bt,int prio){
    if(count>=MAX||pid<0||at<0||bt<=0) return false;
    if(hashSearch(pid)!=-1) return false;

    pro[count]={pid,at,bt,prio,bt,0,0,0};

    int slot=hashFunc(pid);
    while(hashTable[slot]!=-1) slot=(slot+1)%101;
    hashTable[slot]=count;

    count++;
    return true;
}

// remove last process (for undo stack)
bool ProcessTable::removeLast(){
    if(count==0) return false;
    count--;
    for(int i=0;i<101;i++) hashTable[i]=-1;
    for(int i=0;i<count;i++){
        int slot=hashFunc(pro[i].pid);
        while(hashTable[slot]!=-1) slot=(slot+1)%101;
        hashTable[slot]=i;
    }
    return true;
}

int ProcessTable::getCount() const{
    return count;
}

Process& ProcessTable::getProcess(int index){
    return pro[index];
}

const Process& ProcessTable::getProcess(int index) const{
    return pro[index];
}

// linear search
int ProcessTable::linearSearch(int pid) const{
    for(int i=0;i<count;i++){
        if(pro[i].pid==pid) return i;
    }
    return -1;
}

// binary search on sorted indices
int ProcessTable::binarySearch(int pid) const{
    int idx[MAX];
    for(int i=0;i<count;i++) idx[i]=i;
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(pro[idx[j]].pid>pro[idx[j+1]].pid){
                int t=idx[j]; idx[j]=idx[j+1]; idx[j+1]=t;
            }
        }
    }
    int low=0,high=count-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(pro[idx[mid]].pid==pid) return idx[mid];
        if(pro[idx[mid]].pid<pid) low=mid+1;
        else high=mid-1;
    }
    return -1;
}

// hash search with linear probing
int ProcessTable::hashSearch(int pid) const{
    if(pid<0) return -1;
    int slot=hashFunc(pid);
    int probes=0;
    while(hashTable[slot]!=-1&&probes<101){
        int idx=hashTable[slot];
        if(pro[idx].pid==pid) return idx;
        slot=(slot+1)%101;
        probes++;
    }
    return -1;
}

// display all processes
void ProcessTable::display() const{
    cout<<"\nPID\tArrival\tBurst\tPriority\n";
    for(int i=0;i<count;i++){
        cout<<pro[i].pid<<"\t"<<pro[i].at<<"\t"<<pro[i].bt<<"\t"<<pro[i].prio<<"\n";
    }
}
