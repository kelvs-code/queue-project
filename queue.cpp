// Clinic Queue Desk - circular queue (FIFO) implemented with an array
// Compile: g++ queue.cpp -o queue      Run: ./queue   (Windows: queue.exe)
#include <iostream>
#include <string>
using namespace std;

class ClinicQueue {
    static const int CAPACITY = 8;   // chairs in the waiting room
    string patients[CAPACITY];       // the array that holds the queue
    int front = 0;                   // index of the patient served next
    int count = 0;                   // how many patients are waiting

public:
    bool isEmpty() const { return count == 0; }
    bool isFull()  const { return count == CAPACITY; }

    // enqueue: add a patient at the rear. O(1)
    bool enqueue(const string& name) {
        if (isFull()) return false;
        int rear = (front + count) % CAPACITY;  // wraps around the array
        patients[rear] = name;
        count++;
        return true;
    }

    // dequeue: remove the patient at the front. O(1)
    bool dequeue(string& name) {
        if (isEmpty()) return false;
        name = patients[front];
        front = (front + 1) % CAPACITY;         // wraps around the array
        count--;
        return true;
    }

    // peek: look at the front patient without removing. O(1)
    bool peek(string& name) const {
        if (isEmpty()) return false;
        name = patients[front];
        return true;
    }

    void display() const {
        if (isEmpty()) { cout << "Waiting room is empty.\n"; return; }
        cout << "Waiting (front -> rear): ";
        for (int i = 0; i < count; i++)
            cout << "[" << patients[(front + i) % CAPACITY] << "] ";
        cout << "\n";
    }

    int size() const { return count; }
};

int main() {
    ClinicQueue q;
    int choice;
    string name;

    do {
        cout << "\n=== Clinic Queue Desk ===\n"
             << "1. Take a ticket (enqueue)\n"
             << "2. Call next patient (dequeue)\n"
             << "3. Who is next? (peek)\n"
             << "4. Show waiting room\n"
             << "0. Close desk\n"
             << "Choose: ";
        if (!(cin >> choice)) break;
        cin.ignore(1000, '\n');

        switch (choice) {
        case 1:
            cout << "Patient name: ";
            getline(cin, name);
            if (q.enqueue(name))
                cout << name << " took ticket #" << q.size() << " in line.\n";
            else
                cout << "Waiting room is full. Ask the patient to return later.\n";
            break;
        case 2:
            if (q.dequeue(name)) cout << "Now serving: " << name << "\n";
            else cout << "Nobody is waiting.\n";
            break;
        case 3:
            if (q.peek(name)) cout << "Next in line: " << name << "\n";
            else cout << "Nobody is waiting.\n";
            break;
        case 4:
            q.display();
            break;
        case 0:
            cout << "Desk closed. Waiting patients: " << q.size() << "\n";
            break;
        default:
            cout << "Invalid choice. Enter 0-4.\n";
        }
    } while (choice != 0);

    return 0;
}
