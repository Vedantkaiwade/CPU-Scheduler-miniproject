#include "Scheduler.h"
#include <iostream>
#include <iomanip>

using namespace std;

// gantt chart interval entry
struct GanttEntry{
    int pid;
    int start;
    int end;
};

// reset process metrics before each run
void resetProcessMetrics(ProcessTable& pt){
    for(int i=0;i<pt.getCount();i++){
        Process& p=pt.getProcess(i);
        p.remaining=p.bt;
        p.ct=0;
        p.wt=0;
        p.tat=0;
    }
}

static void printGanttAndResults(ProcessTable& pt,GanttEntry* gantt,int gCount,
                                 const char* title,const char* policyName,
                                 RunHistory* history){
    cout<<"\n--- "<<title<<" ---\n";

    // build gantt chart string
    string top="|",bottom="0";
    for(int i=0;i<gCount;i++){
        string label=(gantt[i].pid==-1)?" IDLE ":" P"+to_string(gantt[i].pid)+" ";
        top+=label+"|";

        string t=to_string(gantt[i].end);
        while(bottom.length()<top.length()-t.length()){
            bottom+=" ";
        }
        bottom+=t;
    }

    cout<<"\nGantt Chart:\n";
    cout<<top<<"\n"<<bottom<<"\n\n";
    string fullGantt=top+"\n"+bottom;

    int n=pt.getCount();
    int* idx=new int[n];
    for(int i=0;i<n;i++) idx[i]=i;
    bubbleSortByPID(pt,idx,n);

    cout<<"------------------------------------------------------\n";
    cout<<"PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    cout<<"------------------------------------------------------\n";

    double totalWT=0,totalTAT=0;
    for(int i=0;i<n;i++){
        const Process& p=pt.getProcess(idx[i]);
        totalWT+=p.wt;
        totalTAT+=p.tat;
        cout<<p.pid<<"\t"
            <<p.at<<"\t"
            <<p.bt<<"\t"
            <<p.ct<<"\t\t"
            <<p.wt<<"\t"
            <<p.tat<<"\n";
    }
    cout<<"------------------------------------------------------\n";
    delete[] idx;

    double avgWT=(n>0)?(totalWT/n):0.0;
    double avgTAT=(n>0)?(totalTAT/n):0.0;

    cout<<fixed<<setprecision(2);
    cout<<"Average Waiting Time: "<<avgWT<<"\n";
    cout<<"Average Turnaround Time: "<<avgTAT<<"\n";

    if(history!=nullptr){
        history->addRun(policyName,avgWT,avgTAT,fullGantt);
    }
}

void runFCFS(ProcessTable& pt,RunHistory* history){
    int n=pt.getCount();
    if(n==0) return;
    resetProcessMetrics(pt);

    int* order=new int[n];
    for(int i=0;i<n;i++) order[i]=i;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(pt.getProcess(order[j]).at>pt.getProcess(order[j+1]).at){
                int t=order[j]; order[j]=order[j+1]; order[j+1]=t;
            }
        }
    }

    GanttEntry* gantt=new GanttEntry[n*2+1];
    int gCount=0,curTime=0;

    for(int i=0;i<n;i++){
        Process& p=pt.getProcess(order[i]);
        if(curTime<p.at){
            gantt[gCount++]={-1,curTime,p.at};
            curTime=p.at;
        }

        int start=curTime;
        curTime+=p.bt;
        p.ct=curTime;
        p.tat=p.ct-p.at;
        p.wt=p.tat-p.bt;
        p.remaining=0;

        gantt[gCount++]={p.pid,start,curTime};
    }
    delete[] order;

    printGanttAndResults(pt,gantt,gCount,"First-Come, First-Served (FCFS)","FCFS",history);
    delete[] gantt;
}

// 2. SJF non-preemptive using selection sort
void runSJF(ProcessTable& pt,RunHistory* history){
    int n=pt.getCount();
    if(n==0) return;
    resetProcessMetrics(pt);

    bool* done=new bool[n]();
    int* ready=new int[n];
    GanttEntry* gantt=new GanttEntry[n*2+1];
    int gCount=0,curTime=0,finished=0;

    while(finished<n){
        int rCount=0;
        for(int i=0;i<n;i++){
            if(!done[i]&&pt.getProcess(i).at<=curTime){
                ready[rCount++]=i;
            }
        }

        if(rCount==0){
            int nextArr=1e9;
            for(int i=0;i<n;i++){
                if(!done[i]&&pt.getProcess(i).at<nextArr)
                    nextArr=pt.getProcess(i).at;
            }
            gantt[gCount++]={-1,curTime,nextArr};
            curTime=nextArr;
            continue;
        }

        selectionSortByBurst(pt,ready,rCount);

        int pick=ready[0];
        Process& p=pt.getProcess(pick);

        int start=curTime;
        curTime+=p.bt;
        p.ct=curTime;
        p.tat=p.ct-p.at;
        p.wt=p.tat-p.bt;
        p.remaining=0;

        done[pick]=true;
        finished++;
        gantt[gCount++]={p.pid,start,curTime};
    }

    delete[] done;
    delete[] ready;

    printGanttAndResults(pt,gantt,gCount,"Shortest Job First (SJF)","SJF",history);
    delete[] gantt;
}

// 3. Priority non-preemptive using quick sort (lower number = higher priority)
void runPriority(ProcessTable& pt,RunHistory* history){
    int n=pt.getCount();
    if(n==0) return;
    resetProcessMetrics(pt);

    bool* done=new bool[n]();
    int* ready=new int[n];
    GanttEntry* gantt=new GanttEntry[n*2+1];
    int gCount=0,curTime=0,finished=0;

    while(finished<n){
        int rCount=0;
        for(int i=0;i<n;i++){
            if(!done[i]&&pt.getProcess(i).at<=curTime){
                ready[rCount++]=i;
            }
        }

        if(rCount==0){
            int nextArr=1e9;
            for(int i=0;i<n;i++){
                if(!done[i]&&pt.getProcess(i).at<nextArr)
                    nextArr=pt.getProcess(i).at;
            }
            gantt[gCount++]={-1,curTime,nextArr};
            curTime=nextArr;
            continue;
        }

        quickSortByPriority(pt,ready,0,rCount-1);

        int pick=ready[0];
        Process& p=pt.getProcess(pick);

        int start=curTime;
        curTime+=p.bt;
        p.ct=curTime;
        p.tat=p.ct-p.at;
        p.wt=p.tat-p.bt;
        p.remaining=0;

        done[pick]=true;
        finished++;
        gantt[gCount++]={p.pid,start,curTime};
    }

    delete[] done;
    delete[] ready;

    printGanttAndResults(pt,gantt,gCount,"Priority Scheduling","Priority",history);
    delete[] gantt;
}

// 4. Round Robin using CircularQueue
void runRoundRobin(ProcessTable& pt,int timeQuantum,RunHistory* history){
    int n=pt.getCount();
    if(n==0||timeQuantum<=0) return;
    resetProcessMetrics(pt);

    int* order=new int[n];
    for(int i=0;i<n;i++) order[i]=i;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(pt.getProcess(order[j]).at>pt.getProcess(order[j+1]).at){
                int t=order[j]; order[j]=order[j+1]; order[j+1]=t;
            }
        }
    }

    CircularQueue queue;
    GanttEntry* gantt=new GanttEntry[500];
    int gCount=0,curTime=0,arrIdx=0,finished=0;

    if(pt.getProcess(order[0]).at>0){
        gantt[gCount++]={-1,0,pt.getProcess(order[0]).at};
        curTime=pt.getProcess(order[0]).at;
    }

    while(arrIdx<n&&pt.getProcess(order[arrIdx]).at<=curTime){
        queue.enqueue(order[arrIdx++]);
    }

    while(finished<n){
        if(queue.isEmpty()){
            if(arrIdx<n){
                int nextArr=pt.getProcess(order[arrIdx]).at;
                gantt[gCount++]={-1,curTime,nextArr};
                curTime=nextArr;
                while(arrIdx<n&&pt.getProcess(order[arrIdx]).at<=curTime){
                    queue.enqueue(order[arrIdx++]);
                }
            }else break;
        }

        int curr=queue.dequeue();
        Process& p=pt.getProcess(curr);

        int slice=(p.remaining<timeQuantum)?p.remaining:timeQuantum;
        int start=curTime;
        curTime+=slice;
        p.remaining-=slice;

        // merge consecutive execution for same process
        if(gCount>0&&gantt[gCount-1].pid==p.pid&&gantt[gCount-1].end==start){
            gantt[gCount-1].end=curTime;
        }else{
            gantt[gCount++]={p.pid,start,curTime};
        }

        // admit new arrivals before re-enqueuing
        while(arrIdx<n&&pt.getProcess(order[arrIdx]).at<=curTime){
            queue.enqueue(order[arrIdx++]);
        }

        if(p.remaining==0){
            p.ct=curTime;
            p.tat=p.ct-p.at;
            p.wt=p.tat-p.bt;
            finished++;
        }else{
            queue.enqueue(curr);
        }
    }

    delete[] order;

    string title="Round Robin [Quantum = "+to_string(timeQuantum)+"]";
    printGanttAndResults(pt,gantt,gCount,title.c_str(),"Round Robin",history);
    delete[] gantt;
}
