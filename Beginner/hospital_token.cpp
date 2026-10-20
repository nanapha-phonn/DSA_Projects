
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Patient {
    int token;
    string name;
};

queue<Patient> hospitalQueue;
int nextToken = 1;

// Register a new patient
void registerPatient() {
    Patient p;

    p.token = nextToken++;

    cout << "Enter patient name: ";
    cin >> ws;
    getline(cin, p.name);

    hospitalQueue.push(p);

    cout << "Patient registered successfully!\n";
    cout << "Your token number is: " << p.token << endl;
}

// Serve the next patient
void servePatient() {
    if (hospitalQueue.empty()) {
        cout << "No patients waiting.\n";
        return;
    }

    Patient p = hospitalQueue.front();

    cout << "Now serving token: " << p.token << endl;
    cout << "Patient name: " << p.name << endl;

    hospitalQueue.pop();
}

// Display all waiting patients
void displayQueue() {
    if (hospitalQueue.empty()) {
        cout << "No patients waiting.\n";
        return;
    }

    queue<Patient> temp = hospitalQueue;

    cout << "\n--- Waiting Patients ---\n";

    while (!temp.empty()) {
        Patient p = temp.front();

        cout << "Token: " << p.token
             << " | Name: " << p.name << endl;

        temp.pop();
    }
}

int main() {
    int choice;

    do {
        cout << "\n=== Hospital Token System ===\n";
        cout << "1. Register Patient\n";
        cout << "2. Serve Next Patient\n";
        cout << "3. Display Waiting Queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }

        switch (choice) {
            case 1:
                registerPatient();
                break;

            case 2:
                servePatient();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                cout << "Hospital system closed.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
