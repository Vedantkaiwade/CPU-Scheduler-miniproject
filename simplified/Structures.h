#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <string>
using namespace std;

// 1. circular singly linked list for Round Robin
struct CircularNode{
    int index;
    CircularNode* next;
    CircularNode(int i):index(i),next(nullptr){}
};

class CircularQueue{
private:
    CircularNode* tail;
public:
    CircularQueue():tail(nullptr){}
    ~CircularQueue();
    bool isEmpty() const { return tail==nullptr; }
    void enqueue(int idx);
    int dequeue();
};

// 2. deque for admission and urgent processes
struct DequeNode{
    int index;
    DequeNode* next;
    DequeNode* prev;
    DequeNode(int i):index(i),next(nullptr),prev(nullptr){}
};

class ProcessDeque{
private:
    DequeNode* front;
    DequeNode* rear;
public:
    ProcessDeque():front(nullptr),rear(nullptr){}
    ~ProcessDeque();
    bool isEmpty() const { return front==nullptr; }
    void addFront(int idx);
    void addRear(int idx);
    int removeFront();
    void display() const;
};

// 3. stack for undo log
struct StackNode{
    int index;
    StackNode* next;
    StackNode(int i):index(i),next(nullptr){}
};

class UndoStack{
private:
    StackNode* top;
public:
    UndoStack():top(nullptr){}
    ~UndoStack();
    bool isEmpty() const { return top==nullptr; }
    void push(int idx);
    int pop();
};

// 4. binary search tree for process directory
struct BSTNode{
    int pid;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int id):pid(id),left(nullptr),right(nullptr){}
};

class ProcessBST{
private:
    BSTNode* root;
    BSTNode* insertNode(BSTNode* node,int pid);
    bool searchNode(BSTNode* node,int pid) const;
    void inorder(BSTNode* node) const;
    void destroy(BSTNode* node);
public:
    ProcessBST():root(nullptr){}
    ~ProcessBST(){ destroy(root); }
    void insert(int pid){ root=insertNode(root,pid); }
    bool search(int pid) const { return searchNode(root,pid); }
    void displayInorder() const { inorder(root); cout<<"\n"; }
};

// 5. doubly linked list for run history
struct HistoryNode{
    string policy;
    double avgWT;
    double avgTAT;
    string gantt;
    HistoryNode* prev;
    HistoryNode* next;
    HistoryNode(string p,double wt,double tat,string g)
        :policy(p),avgWT(wt),avgTAT(tat),gantt(g),prev(nullptr),next(nullptr){}
};

class RunHistory{
private:
    HistoryNode* head;
    HistoryNode* tail;
    HistoryNode* current;
public:
    RunHistory():head(nullptr),tail(nullptr),current(nullptr){}
    ~RunHistory();
    bool isEmpty() const { return head==nullptr; }
    void addRun(string policy,double avgWT,double avgTAT,string gantt);
    bool movePrev();
    bool moveNext();
    void displayCurrent() const;
    void displayAll() const;
};

#endif
