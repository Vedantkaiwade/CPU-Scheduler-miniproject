#include <iostream>
#include "Process.h"
#include "Sorting.h"
#include "Structures.h"
#include "Scheduler.h"

using namespace std;

// display main CLI menu
void displayMenu(){
    cout<<"\n=========================================\n";
    cout<<"       CPU SCHEDULING SIMULATOR          \n";
    cout<<"=========================================\n";
    cout<<" 1. Add Process\n";
    cout<<" 2. Add Urgent Process (Deque Front)\n";
    cout<<" 3. Undo Last Process Addition (Stack)\n";
    cout<<" 4. Display Process Table\n";
    cout<<" 5. Search Process (Linear / Binary / Hash / BST)\n";
    cout<<" 6. Sort Processes (Burst / Priority / PID)\n";
    cout<<" 7. Run FCFS\n";
    cout<<" 8. Run SJF (Non-Preemptive)\n";
    cout<<" 9. Run Priority (Non-Preemptive)\n";
    cout<<" 10. Run Round Robin\n";
    cout<<" 11. View Run History (Doubly Linked List)\n";
    cout<<" 12. Load Sample Workload\n";
    cout<<" 0. Exit\n";
    cout<<"-----------------------------------------\n";
    cout<<"Enter your choice: ";
}

// load initial sample data
void loadSampleData(ProcessTable& pt,ProcessDeque& deq,UndoStack& undo,ProcessBST& bst){
    int sample[4][4]={{1,0,7,3},{2,2,4,1},{3,4,1,4},{4,5,4,2}};
    for(int i=0;i<4;i++){
        if(pt.addProcess(sample[i][0],sample[i][1],sample[i][2],sample[i][3])){
            deq.addRear(pt.getCount()-1);
            undo.push(sample[i][0]);
            bst.insert(sample[i][0]);
        }
    }
    cout<<"\nLoaded 4 sample processes successfully!\n";
}

int main(){
    ProcessTable pt;
    ProcessDeque admissionDeque;
    UndoStack undoLog;
    ProcessBST directoryBST;
    RunHistory history;

    int choice;
    while(true){
        displayMenu();
        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(1000,'\n');
            continue;
        }

        if(choice==0){
            cout<<"\nExiting Simulator. Goodbye!\n";
            break;
        }

        switch(choice){
            case 1:{
                int pid,at,bt,prio;
                cout<<"\nEnter Process ID: "; cin>>pid;
                cout<<"Enter Arrival Time: "; cin>>at;
                cout<<"Enter Burst Time: "; cin>>bt;
                cout<<"Enter Priority (lower = higher priority): "; cin>>prio;

                if(pt.addProcess(pid,at,bt,prio)){
                    int idx=pt.getCount()-1;
                    admissionDeque.addRear(idx);
                    undoLog.push(pid);
                    directoryBST.insert(pid);
                    cout<<"Process P"<<pid<<" added successfully!\n";
                }else{
                    cout<<"Failed to add process (Duplicate PID or invalid input).\n";
                }
                break;
            }
            case 2:{
                int pid,at,bt,prio;
                cout<<"\n[Urgent Process Admission]\n";
                cout<<"Enter Process ID: "; cin>>pid;
                cout<<"Enter Arrival Time: "; cin>>at;
                cout<<"Enter Burst Time: "; cin>>bt;
                cout<<"Enter Priority (highest priority): "; cin>>prio;

                if(pt.addProcess(pid,at,bt,prio)){
                    int idx=pt.getCount()-1;
                    admissionDeque.addFront(idx); // added to front of deque
                    undoLog.push(pid);
                    directoryBST.insert(pid);
                    cout<<"Urgent Process P"<<pid<<" added to FRONT of Admission Deque!\n";
                    admissionDeque.display();
                }else{
                    cout<<"Failed to add urgent process.\n";
                }
                break;
            }
            case 3:{
                if(undoLog.isEmpty()){
                    cout<<"\nUndo stack is empty. Nothing to undo.\n";
                }else{
                    int lastPid=undoLog.pop();
                    pt.removeLast();
                    cout<<"\nUndo successful! Removed process P"<<lastPid<<".\n";
                }
                break;
            }
            case 4:
                pt.display();
                admissionDeque.display();
                cout<<"BST Directory Inorder: ";
                directoryBST.displayInorder();
                break;

            case 5:{
                int pid;
                cout<<"\nEnter PID to search: "; cin>>pid;
                cout<<"[1] Linear Search  : "<<((pt.linearSearch(pid)!=-1)?"Found":"Not Found")<<"\n";
                cout<<"[2] Binary Search  : "<<((pt.binarySearch(pid)!=-1)?"Found":"Not Found")<<"\n";
                cout<<"[3] Hash Search    : "<<((pt.hashSearch(pid)!=-1)?"Found":"Not Found")<<"\n";
                cout<<"[4] BST Directory  : "<<(directoryBST.search(pid)?"Found":"Not Found")<<"\n";
                break;
            }
            case 6:{
                int n=pt.getCount();
                if(n==0){ cout<<"\nNo processes to sort.\n"; break; }
                int* idx=new int[n];
                int sChoice;
                cout<<"\nSort by: [1] Burst Time (Selection) [2] Priority (Quick) [3] PID (Bubble): ";
                cin>>sChoice;
                for(int i=0;i<n;i++) idx[i]=i;

                if(sChoice==1){
                    selectionSortByBurst(pt,idx,n);
                    cout<<"Sorted by Burst Time: ";
                }else if(sChoice==2){
                    quickSortByPriority(pt,idx,0,n-1);
                    cout<<"Sorted by Priority: ";
                }else{
                    bubbleSortByPID(pt,idx,n);
                    cout<<"Sorted by PID: ";
                }
                for(int i=0;i<n;i++) cout<<"P"<<pt.getProcess(idx[i]).pid<<" ";
                cout<<"\n";
                delete[] idx;
                break;
            }
            case 7:
                runFCFS(pt,&history);
                break;

            case 8:
                runSJF(pt,&history);
                break;

            case 9:
                runPriority(pt,&history);
                break;

            case 10:{
                int q;
                cout<<"\nEnter Time Quantum: "; cin>>q;
                runRoundRobin(pt,q,&history);
                break;
            }
            case 11:{
                if(history.isEmpty()){
                    cout<<"\nNo runs in history yet.\n";
                    break;
                }
                history.displayAll();
                int hChoice;
                cout<<"\n[1] View Current [2] Move Previous [3] Move Next [0] Back: ";
                cin>>hChoice;
                if(hChoice==1) history.displayCurrent();
                else if(hChoice==2){
                    if(history.movePrev()) history.displayCurrent();
                    else cout<<"Already at oldest run.\n";
                }else if(hChoice==3){
                    if(history.moveNext()) history.displayCurrent();
                    else cout<<"Already at newest run.\n";
                }
                break;
            }
            case 12:
                loadSampleData(pt,admissionDeque,undoLog,directoryBST);
                pt.display();
                break;

            default:
                cout<<"Invalid choice! Enter between 0 and 12.\n";
                break;
        }
    }

    return 0;
}
