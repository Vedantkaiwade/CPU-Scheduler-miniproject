#include <iostream>
using namespace std;

class Process{
    int pID;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
public:
    // Getter for process ID
    int getPID(){
        return pID;
    }
    // Setter for process ID
    void setpID(int id){
        pID = id;
    }
    
    // Arrival Time
    int getArrivalTime() {
        return arrival_time;
    }

    void setArrivalTime(int at) {
        arrival_time = at;
    }

    // Burst Time
    int getBurstTime() {
        return burst_time;
    }

    void setBurstTime(int bt) {
        burst_time = bt;
    }

    // Completion Time
    int getCompletionTime() {
        return completion_time;
    }

    void setCompletionTime(int ct) {
        completion_time = ct;
    }

    // Turnaround Time
    int getTurnaroundTime() {
        return turnaround_time;
    }

    void setTurnaroundTime(int tat) {
        turnaround_time = tat;
    }

    // Waiting Time
    int getWaitingTime() {
        return waiting_time;
    }

    void setWaitingTime(int wt) {
        waiting_time = wt;
    }

};

class ProcessTable{
    static const int SIZE = 100;
    Process pro[SIZE];
    int processCounter = 0;
    Process *HashTable[SIZE * 2 + 1];
public:

    // Initailizing the hash table
    ProcessTable(){
        for(int i=0 ; i < SIZE*2+1 ; i++){
            HashTable[i] = nullptr;
        }
    }

    // Adding a Process
    Process* addProcess(Process P){
        if(processCounter < SIZE){
            pro[processCounter] = P;
            return &pro[processCounter++];
        }
        else{
            cout<<"Table is Full!\n";
            return nullptr;
        }
    }

    // Finding a Process
    Process *findProcess(int pid){
        for(int i=0;i<processCounter;i++){
            if(pro[i].getPID() == pid){
                cout<<"Process found ";
                return &pro[i];
            }
        }
        cout<<"Invald Process ID\n";
        return nullptr;
    }

    // Hash Function
    int HashFunction(int ID){
        int result = ID % (SIZE*2+1);
        return result;
    }

    // Collision Resolution
    int LinearProbing(int index){
        for(int i=0;i<SIZE*2+1;i++){
            int current = (index + i) % (SIZE*2+1);
            if(HashTable[current]==nullptr){
                return current;
            }
        }
        return -1; //hash table is full
    }

    // HashTable Insertion
void InsertIntoHash(Process *P) {
    if (P == nullptr) {
        return;
    }

    bool isDuplicate = HashSearch(P->getPID());

    if (isDuplicate) {
        cout << "Process already exists\n";
        return;
    }

    int index = HashFunction(P->getPID());
    int slot = LinearProbing(index);

    if (slot == -1) {
        cout << "Hash table is full!\n";
        return;
    }

    HashTable[slot] = P;
    cout << "Process inserted at index " << slot << endl;
}

// Search using Hash Table
bool HashSearch(int PID) {
    int index = HashFunction(PID);
    int tableSize = SIZE * 2 + 1;

    for (int i = 0; i < tableSize; i++) {
        int current = (index + i) % tableSize;

        if (HashTable[current] == nullptr) {
            return false;
        }

        if (HashTable[current]->getPID() == PID) {
            return true;
        }
    }

    return false;
}

// Display search result separately
void DisplayHashSearch(int PID) {
    if (HashSearch(PID)) {
        cout << "Process with PID " << PID << " found.\n";
    } else {
        cout << "Process with PID " << PID << " not found.\n";
    }
}


void FCFS() {
    if (processCounter == 0) {
        cout << "No processes available!\n";
        return;
    }

    // Temporary array: do not change the original process order
    Process* order[SIZE];

    for (int i = 0; i < processCounter; i++) {
        order[i] = &pro[i];
    }

    // Stable insertion sort by arrival time
    for (int i = 1; i < processCounter; i++) {
        Process* key = order[i];
        int j = i - 1;

        while (j >= 0 &&
               order[j]->getArrivalTime() >
               key->getArrivalTime()) {
            order[j + 1] = order[j];
            j--;
        }

        order[j + 1] = key;
    }

    int currentTime = 0;

    cout << "\nFCFS Scheduling\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";

    // For avg waiting time and turn around time
    double totalWT = 0;
    double totalTAT = 0;

    for (int i = 0; i < processCounter; i++) {
        Process* p = order[i];

        int at = p->getArrivalTime();
        int bt = p->getBurstTime();

        // Handle CPU idle time
        int startTime = (currentTime > at) ? currentTime : at;

        int ct = startTime + bt;
        int tat = ct - at;
        int wt = tat - bt;

        totalWT += wt;
        totalTAT += tat;    

        p->setCompletionTime(ct);
        p->setTurnaroundTime(tat);
        p->setWaitingTime(wt);

        cout << p->getPID() << "\t"
             << at << "\t"
             << bt << "\t"
             << ct << "\t"
             << tat << "\t"
             << wt << "\n";

        currentTime = ct;
    }
    cout << "\nAverage Waiting Time: "<< totalWT / processCounter << endl;

    cout << "Average Turnaround Time: "<< totalTAT / processCounter << endl;
}


};

int main() {
    Process P1, P2, P3;
ProcessTable table;

P1.setpID(1);
P1.setArrivalTime(0);
P1.setBurstTime(5);

P2.setpID(2);
P2.setArrivalTime(1);
P2.setBurstTime(3);

P3.setpID(3);
P3.setArrivalTime(2);
P3.setBurstTime(2);

table.addProcess(P1);
table.addProcess(P2);
table.addProcess(P3);

table.FCFS();

    return 0;
}