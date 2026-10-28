#include "Structures.h"

// 1. circular singly linked list for Round Robin
CircularQueue::~CircularQueue(){
    while(!isEmpty()) dequeue();
}
void CircularQueue::enqueue(int idx){
    CircularNode* n=new CircularNode(idx);
    if(isEmpty()){
        tail=n;
        n->next=n;
    }else{
        n->next=tail->next;
        tail->next=n;
        tail=n;
    }
}
int CircularQueue::dequeue(){
    if(isEmpty()) return -1;
    CircularNode* first=tail->next;
    int idx=first->index;
    if(first==tail) tail=nullptr;
    else tail->next=first->next;
    delete first;
    return idx;
}

// 2. deque for admission queue
ProcessDeque::~ProcessDeque(){
    while(!isEmpty()) removeFront();
}
void ProcessDeque::addFront(int idx){
    DequeNode* n=new DequeNode(idx);
    if(isEmpty()) front=rear=n;
    else{ n->next=front; front->prev=n; front=n; }
}
void ProcessDeque::addRear(int idx){
    DequeNode* n=new DequeNode(idx);
    if(isEmpty()) front=rear=n;
    else{ rear->next=n; n->prev=rear; rear=n; }
}
int ProcessDeque::removeFront(){
    if(isEmpty()) return -1;
    DequeNode* t=front;
    int idx=t->index;
    front=front->next;
    if(front) front->prev=nullptr;
    else rear=nullptr;
    delete t;
    return idx;
}
void ProcessDeque::display() const{
    if(isEmpty()){ cout<<"Deque is empty.\n"; return; }
    cout<<"Admission Deque: ";
    for(DequeNode* c=front;c!=nullptr;c=c->next) cout<<"P"<<c->index<<" ";
    cout<<"\n";
}

// 3. stack for undo log
UndoStack::~UndoStack(){
    while(!isEmpty()) pop();
}
void UndoStack::push(int idx){
    StackNode* n=new StackNode(idx);
    n->next=top;
    top=n;
}
int UndoStack::pop(){
    if(isEmpty()) return -1;
    StackNode* t=top;
    int idx=t->index;
    top=top->next;
    delete t;
    return idx;
}

// 4. binary search tree for process directory
BSTNode* ProcessBST::insertNode(BSTNode* node,int pid){
    if(!node) return new BSTNode(pid);
    if(pid<node->pid) node->left=insertNode(node->left,pid);
    else if(pid>node->pid) node->right=insertNode(node->right,pid);
    return node;
}
bool ProcessBST::searchNode(BSTNode* node,int pid) const{
    if(!node) return false;
    if(node->pid==pid) return true;
    if(pid<node->pid) return searchNode(node->left,pid);
    return searchNode(node->right,pid);
}
void ProcessBST::inorder(BSTNode* node) const{
    if(!node) return;
    inorder(node->left);
    cout<<node->pid<<" ";
    inorder(node->right);
}
void ProcessBST::destroy(BSTNode* node){
    if(!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// 5. doubly linked list for run history
RunHistory::~RunHistory(){
    while(head){
        HistoryNode* t=head;
        head=head->next;
        delete t;
    }
}
void RunHistory::addRun(string policy,double avgWT,double avgTAT,string gantt){
    HistoryNode* n=new HistoryNode(policy,avgWT,avgTAT,gantt);
    if(!head) head=tail=current=n;
    else{
        tail->next=n;
        n->prev=tail;
        tail=current=n;
    }
}
bool RunHistory::movePrev(){
    if(current&&current->prev){ current=current->prev; return true; }
    return false;
}
bool RunHistory::moveNext(){
    if(current&&current->next){ current=current->next; return true; }
    return false;
}
void RunHistory::displayCurrent() const{
    if(!current){ cout<<"No run history.\n"; return; }
    cout<<"\n--- History: "<<current->policy<<" ---\n";
    cout<<current->gantt<<"\n";
    cout<<"Avg Waiting Time: "<<current->avgWT<<"\n";
    cout<<"Avg Turnaround Time: "<<current->avgTAT<<"\n";
}
void RunHistory::displayAll() const{
    if(!head){ cout<<"Run history is empty.\n"; return; }
    cout<<"\n--- Completed Runs ---\n";
    int i=1;
    for(HistoryNode* c=head;c!=nullptr;c=c->next){
        cout<<i++<<". "<<c->policy<<" | Avg WT: "<<c->avgWT<<" | Avg TAT: "<<c->avgTAT;
        if(c==current) cout<<" (Current)";
        cout<<"\n";
    }
}
