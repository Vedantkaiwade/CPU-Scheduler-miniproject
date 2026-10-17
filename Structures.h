
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
using namespace std;

// ==================================================
// 1. CIRCULAR SINGLY LINKED LIST
// Used for Round Robin ready queue
// ==================================================

struct CircularNode {
    int processIndex;
    CircularNode* next;

    CircularNode(int index);
};

class CircularLinkedList {
private:
    CircularNode* tail;
    int count;

public:
    CircularLinkedList();
    ~CircularLinkedList();

    bool isEmpty() const;
    int getCount() const;

    void enqueue(int processIndex);
    int dequeue();
    void display() const;
};


// ==================================================
// 2. DEQUE
// Used for process admission queue
// ==================================================

struct DequeNode {
    int processIndex;
    DequeNode* next;
    DequeNode* prev;

    DequeNode(int index);
};

class ProcessDeque {
private:
    DequeNode* front;
    DequeNode* rear;
    int count;

public:
    ProcessDeque();
    ~ProcessDeque();

    bool isEmpty() const;
    int getCount() const;

    void addFront(int processIndex);
    void addRear(int processIndex);

    int removeFront();
    int removeRear();

    void display() const;
};


// ==================================================
// 3. STACK
// Used for undo log
// ==================================================

struct StackNode {
    int processIndex;
    StackNode* next;

    StackNode(int index);
};

class UndoStack {
private:
    StackNode* topNode;
    int count;

public:
    UndoStack();
    ~UndoStack();

    bool isEmpty() const;
    int getCount() const;

    void push(int processIndex);
    int pop();
    int peek() const;

    void display() const;
};


// ==================================================
// 4. DOUBLY LINKED LIST
// Used for scheduling run history
// ==================================================

struct HistoryNode {
    int runId;
    HistoryNode* next;
    HistoryNode* prev;

    HistoryNode(int id);
};

class RunHistory {
private:
    HistoryNode* head;
    HistoryNode* tail;
    HistoryNode* current;
    int count;

public:
    RunHistory();
    ~RunHistory();

    bool isEmpty() const;
    int getCount() const;

    // Add a new run to history
    void addRun(int runId);

    // Navigate history
    int moveBackward();
    int moveForward();

    // Get current run without moving
    int getCurrentRun() const;

    void display() const;
};


// ==================================================
// 5. BINARY SEARCH TREE
// Used for process directory
// ==================================================

struct TreeNode {
    int processId;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int id);
};

class ProcessBST {
private:
    TreeNode* root;

    TreeNode* insertNode(TreeNode* node, int processId);
    bool searchNode(TreeNode* node, int processId) const;

    void inorderTraversal(TreeNode* node) const;
    void preorderTraversal(TreeNode* node) const;
    void postorderTraversal(TreeNode* node) const;

    void deleteTree(TreeNode* node);

public:
    ProcessBST();
    ~ProcessBST();

    void insert(int processId);
    bool search(int processId) const;

    void displayInorder() const;
    void displayPreorder() const;
    void displayPostorder() const;
};

#endif
