
#include <iostream>
#include "process.h"
using namespace std;

int main() {
    ProcessTable pt(3);

    cout << boolalpha;

    cout << "Adding P1: "
         << pt.addProcess(1, 0, 7, 2) << "\n";

    cout << "Adding P2: "
         << pt.addProcess(2, 1, 3, 1) << "\n";

    cout << "Adding P3: "
         << pt.addProcess(3, 2, 5, 3) << "\n";

    cout << "Adding duplicate P1: "
         << pt.addProcess(1, 4, 6, 2) << "\n";

    pt.displayAll();

    cout << "\nLinear search for PID 2: "
         << pt.linearSearchByPID(2) << "\n";

    cout << "Binary search for PID 3: "
         << pt.binarySearchByPID(3) << "\n";

    cout << "Hash search for PID 1: "
         << pt.hashSearchByPID(1) << "\n";

    cout << "Hash search for PID 99: "
         << pt.hashSearchByPID(99) << "\n";

    return 0;
}
