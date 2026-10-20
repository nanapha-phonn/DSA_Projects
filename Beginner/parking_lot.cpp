
#include <iostream>
#include <string>
using namespace std;

int main() {
    string cars[10];
    int totalSlots = 10;
    int choice;

    // Empty spaces at the beginning
    for (int i = 0; i < totalSlots; i++) {
        cars[i] = "";
    }

    while (true) {
        cout << "\n=== Parking Lot Management System ===\n";
        cout << "1. Park a Vehicle\n";
        cout << "2. Remove a Vehicle\n";
        cout << "3. Show Parking Lot\n";
        cout << "4. Show Available Spaces\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string plate;
            bool parked = false;

            cout << "Enter vehicle plate number: ";
            cin >> plate;

            for (int i = 0; i < totalSlots; i++) {
                if (cars[i] == plate) {
                    cout << "This vehicle is already parked.\n";
                    parked = true;
                    break;
                }
            }

            if (!parked) {
                for (int i = 0; i < totalSlots; i++) {
                    if (cars[i] == "") {
                        cars[i] = plate;
                        cout << "Vehicle parked at slot "
                             << i + 1 << endl;
                        parked = true;
                        break;
                    }
                }

                if (!parked) {
                    cout << "Parking lot is full!\n";
                }
            }
        }
        else if (choice == 2) {
            string plate;
            bool found = false;

            cout << "Enter vehicle plate to remove: ";
            cin >> plate;

            for (int i = 0; i < totalSlots; i++) {
                if (cars[i] == plate) {
                    cars[i] = "";
                    cout << "Vehicle removed from slot "
                         << i + 1 << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Vehicle not found.\n";
            }
        }
        else if (choice == 3) {
            cout << "\n--- Parking Lot Status ---\n";

            for (int i = 0; i < totalSlots; i++) {
                cout << "Slot " << i + 1 << ": ";

                if (cars[i] == "") {
                    cout << "Available";
                }
                else {
                    cout << cars[i];
                }

                cout << endl;
            }
        }
        else if (choice == 4) {
            int available = 0;

            for (int i = 0; i < totalSlots; i++) {
                if (cars[i] == "") {
                    available++;
                }
            }

            cout << "Total parking slots: "
                 << totalSlots << endl;
            cout << "Available spaces: "
                 << available << endl;
            cout << "Occupied spaces: "
                 << totalSlots - available << endl;
        }
        else if (choice == 5) {
            cout << "Parking system closed.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
