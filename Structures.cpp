
#include "Structures.h"

// ==================================================
// 1. CIRCULAR SINGLY LINKED LIST IMPLEMENTATION
// ==================================================

CircularNode::CircularNode(int index) {
    processIndex = index;
    next = nullptr;
}

CircularLinkedList::CircularLinkedList() {
    tail = nullptr;
    count = 0;
}

CircularLinkedList::~CircularLinkedList() {
    while (!isEmpty()) {
        dequeue();
    }
}

bool CircularLinkedList::isEmpty() const {
    return tail == nullptr;
}

int CircularLinkedList::getCount() const {
    return count;
}

void CircularLinkedList::enqueue(int processIndex) {
    CircularNode* newNode = new CircularNode(processIndex);

    if (isEmpty()) {
        tail = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }

    count++;
}

int CircularLinkedList::dequeue() {
    if (isEmpty()) {
        return -1;
    }

    CircularNode* first = tail->next;
    int index = first->processIndex;

    if (first == tail) {
        tail = nullptr;
    } else {
        tail->next = first->next;
    }

    delete first;
    count--;

    return index;
}

void CircularLinkedList::display() const {
    if (isEmpty()) {
        cout << "Circular queue is empty.\n";
        return;
    }

    CircularNode* currentNode = tail->next;

    cout << "Circular queue: ";

    do {
        cout << "P" << currentNode->processIndex << " ";
        currentNode = currentNode->next;
    } while (currentNode != tail->next);

    cout << '\n';
}


// ==================================================
// 2. DEQUE IMPLEMENTATION
// ==================================================

DequeNode::DequeNode(int index) {
    processIndex = index;
    next = nullptr;
    prev = nullptr;
}

ProcessDeque::ProcessDeque() {
    front = nullptr;
    rear = nullptr;
    count = 0;
}

ProcessDeque::~ProcessDeque() {
    while (!isEmpty()) {
        removeFront();
    }
}

bool ProcessDeque::isEmpty() const {
    return front == nullptr;
}

int ProcessDeque::getCount() const {
    return count;
}

void ProcessDeque::addFront(int processIndex) {
    DequeNode* newNode = new DequeNode(processIndex);

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    }

    count++;
}

void ProcessDeque::addRear(int processIndex) {
    DequeNode* newNode = new DequeNode(processIndex);

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        newNode->prev = rear;
        rear = newNode;
    }

    count++;
}

int ProcessDeque::removeFront() {
    if (isEmpty()) {
        return -1;
    }

    DequeNode* temp = front;
    int index = temp->processIndex;

    front = front->next;

    if (front != nullptr) {
        front->prev = nullptr;
    } else {
        rear = nullptr;
    }

    delete temp;
    count--;

    return index;
}

int ProcessDeque::removeRear() {
    if (isEmpty()) {
        return -1;
    }

    DequeNode* temp = rear;
    int index = temp->processIndex;

    rear = rear->prev;

    if (rear != nullptr) {
        rear->next = nullptr;
    } else {
        front = nullptr;
    }

    delete temp;
    count--;

    return index;
}

void ProcessDeque::display() const {
    if (isEmpty()) {
        cout << "Admission deque is empty.\n";
        return;
    }

    DequeNode* node = front;

    cout << "Admission deque: ";

    while (node != nullptr) {
        cout << "P" << node->processIndex << " ";
        node = node->next;
    }

    cout << '\n';
}


// ==================================================
// 3. STACK IMPLEMENTATION
// ==================================================

StackNode::StackNode(int index) {
    processIndex = index;
    next = nullptr;
}

UndoStack::UndoStack() {
    topNode = nullptr;
    count = 0;
}

UndoStack::~UndoStack() {
    while (!isEmpty()) {
        pop();
    }
}

bool UndoStack::isEmpty() const {
    return topNode == nullptr;
}

int UndoStack::getCount() const {
    return count;
}

void UndoStack::push(int processIndex) {
    StackNode* newNode = new StackNode(processIndex);

    newNode->next = topNode;
    topNode = newNode;

    count++;
}

int UndoStack::pop() {
    if (isEmpty()) {
        return -1;
    }

    StackNode* temp = topNode;
    int index = temp->processIndex;

    topNode = topNode->next;

    delete temp;
    count--;

    return index;
}

int UndoStack::peek() const {
    if (isEmpty()) {
        return -1;
    }

    return topNode->processIndex;
}

void UndoStack::display() const {
    if (isEmpty()) {
        cout << "Undo stack is empty.\n";
        return;
    }

    StackNode* node = topNode;

    cout << "Undo stack (top to bottom): ";

    while (node != nullptr) {
        cout << "P" << node->processIndex << " ";
        node = node->next;
    }

    cout << '\n';
}


// ==================================================
// 4. DOUBLY LINKED LIST IMPLEMENTATION
// ==================================================

HistoryNode::HistoryNode(int id) {
    runId = id;
    next = nullptr;
    prev = nullptr;
}

RunHistory::RunHistory() {
    head = nullptr;
    tail = nullptr;
    current = nullptr;
    count = 0;
}

RunHistory::~RunHistory() {
    HistoryNode* node = head;

    while (node != nullptr) {
        HistoryNode* temp = node;
        node = node->next;
        delete temp;
    }
}

bool RunHistory::isEmpty() const {
    return head == nullptr;
}

int RunHistory::getCount() const {
    return count;
}

void RunHistory::addRun(int runId) {
    HistoryNode* newNode = new HistoryNode(runId);

    if (isEmpty()) {
        head = tail = current = newNode;
    } else {
        // If a new run is added after moving backward,
        // remove the forward history.
        HistoryNode* node = current->next;

        while (node != nullptr) {
            HistoryNode* temp = node;
            node = node->next;
            delete temp;
            count--;
        }

        current->next = nullptr;
        tail = current;

        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        current = newNode;
    }

    count++;
}

int RunHistory::moveBackward() {
    if (current == nullptr || current->prev == nullptr) {
        return -1;
    }

    current = current->prev;
    return current->runId;
}

int RunHistory::moveForward() {
    if (current == nullptr || current->next == nullptr) {
        return -1;
    }

    current = current->next;
    return current->runId;
}

int RunHistory::getCurrentRun() const {
    if (current == nullptr) {
        return -1;
    }

    return current->runId;
}

void RunHistory::display() const {
    if (isEmpty()) {
        cout << "Run history is empty.\n";
        return;
    }

    HistoryNode* node = head;

    cout << "Run history: ";

    while (node != nullptr) {
        if (node == current) {
            cout << "[" << node->runId << "] ";
        } else {
            cout << node->runId << " ";
        }

        node = node->next;
    }

    cout << "\nCurrent run: " << current->runId << '\n';
}


// ==================================================
// 5. BINARY SEARCH TREE IMPLEMENTATION
// ==================================================

TreeNode::TreeNode(int id) {
    processId = id;
    left = nullptr;
    right = nullptr;
}

ProcessBST::ProcessBST() {
    root = nullptr;
}

ProcessBST::~ProcessBST() {
    deleteTree(root);
}

TreeNode* ProcessBST::insertNode(TreeNode* node, int processId) {
    if (node == nullptr) {
        return new TreeNode(processId);
    }

    if (processId < node->processId) {
        node->left = insertNode(node->left, processId);
    } else if (processId > node->processId) {
        node->right = insertNode(node->right, processId);
    }
    // Duplicate process IDs are ignored.

    return node;
}

void ProcessBST::insert(int processId) {
    root = insertNode(root, processId);
}

bool ProcessBST::searchNode(TreeNode* node, int processId) const {
    if (node == nullptr) {
        return false;
    }

    if (node->processId == processId) {
        return true;
    }

    if (processId < node->processId) {
        return searchNode(node->left, processId);
    }

    return searchNode(node->right, processId);
}

bool ProcessBST::search(int processId) const {
    return searchNode(root, processId);
}

void ProcessBST::inorderTraversal(TreeNode* node) const {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);
    cout << node->processId << " ";
    inorderTraversal(node->right);
}

void ProcessBST::preorderTraversal(TreeNode* node) const {
    if (node == nullptr) {
        return;
    }

    cout << node->processId << " ";
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void ProcessBST::postorderTraversal(TreeNode* node) const {
    if (node == nullptr) {
        return;
    }

    postorderTraversal(node->left);
    postorderTraversal(node->right);
    cout << node->processId << " ";
}

void ProcessBST::displayInorder() const {
    cout << "BST inorder (sorted IDs): ";
    inorderTraversal(root);
    cout << '\n';
}

void ProcessBST::displayPreorder() const {
    cout << "BST preorder: ";
    preorderTraversal(root);
    cout << '\n';
}

void ProcessBST::displayPostorder() const {
    cout << "BST postorder: ";
    postorderTraversal(root);
    cout << '\n';
}

void ProcessBST::deleteTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
