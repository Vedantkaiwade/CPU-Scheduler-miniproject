
#include "Structures.h"

int main() {
    cout << "===== 1. Circular Linked List =====\n";

    CircularLinkedList rrQueue;
    rrQueue.enqueue(0);
    rrQueue.enqueue(1);
    rrQueue.enqueue(2);
    rrQueue.display();
    cout << "Dequeued: P" << rrQueue.dequeue() << "\n\n";

    cout << "===== 2. Deque =====\n";

    ProcessDeque admission;
    admission.addRear(0);
    admission.addRear(1);
    admission.addFront(2);
    admission.display();
    cout << "Next: P" << admission.removeFront() << "\n\n";

    cout << "===== 3. Undo Stack =====\n";

    UndoStack undo;
    undo.push(0);
    undo.push(1);
    undo.push(2);
    undo.display();
    cout << "Undo: P" << undo.pop() << "\n\n";

    cout << "===== 4. Run History DLL =====\n";

    RunHistory history;
    history.addRun(101);
    history.addRun(102);
    history.addRun(103);
    history.display();

    cout << "Move backward: " << history.moveBackward() << "\n";
    history.display();

    cout << "Move forward: " << history.moveForward() << "\n\n";

    cout << "===== 5. Process BST =====\n";

    ProcessBST tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10);
    tree.insert(25);

    tree.displayInorder();
    tree.displayPreorder();
    tree.displayPostorder();

    cout << "Search for PID 25: "
         << (tree.search(25) ? "Found" : "Not found") << "\n";

    cout << "Search for PID 99: "
         << (tree.search(99) ? "Found" : "Not found") << "\n";

    cout << "\nAll five structure tests completed.\n";

    return 0;
}
