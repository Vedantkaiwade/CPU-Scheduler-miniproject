#include "Sorting.h"

// 1. selection sort by burst time
void selectionSortByBurst(const ProcessTable& pt,int idx[],int n){
    for(int i=0;i<n-1;i++){
        int minIdx=i;
        for(int j=i+1;j<n;j++){
            if(pt.getProcess(idx[j]).bt < pt.getProcess(idx[minIdx]).bt){
                minIdx=j;
            }
        }
        int t=idx[i]; idx[i]=idx[minIdx]; idx[minIdx]=t;
    }
}

// partition for quick sort by priority
int partitionByPriority(const ProcessTable& pt,int idx[],int low,int high){
    int pivotPrio=pt.getProcess(idx[high]).prio;
    int i=low-1;
    for(int j=low;j<high;j++){
        if(pt.getProcess(idx[j]).prio <= pivotPrio){
            i++;
            int t=idx[i]; idx[i]=idx[j]; idx[j]=t;
        }
    }
    int t=idx[i+1]; idx[i+1]=idx[high]; idx[high]=t;
    return i+1;
}

// 2. quick sort by priority (lower number = higher priority)
void quickSortByPriority(const ProcessTable& pt,int idx[],int low,int high){
    if(low<high){
        int p=partitionByPriority(pt,idx,low,high);
        quickSortByPriority(pt,idx,low,p-1);
        quickSortByPriority(pt,idx,p+1,high);
    }
}

// 3. bubble sort by PID
void bubbleSortByPID(const ProcessTable& pt,int idx[],int n){
    for(int i=0;i<n-1;i++){
        bool swapped=false;
        for(int j=0;j<n-i-1;j++){
            if(pt.getProcess(idx[j]).pid > pt.getProcess(idx[j+1]).pid){
                int t=idx[j]; idx[j]=idx[j+1]; idx[j+1]=t;
                swapped=true;
            }
        }
        if(!swapped) break;
    }
}
