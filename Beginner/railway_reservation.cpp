
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Passenger {
    int id;
    string name;
};

class RailwayReservation {
private:
    vector<Passenger> confirmed;
    queue<Passenger> waiting;

    int capacity;
    int nextId = 1001;

public:
    explicit RailwayReservation(int seats)
        : capacity(seats > 0 ? seats : 1) {}

    void bookTicket(const string& name) {
        if (name.empty()) {
            cout << "Passenger name cannot be empty.\n";
            return;
        }

        Passenger passenger{nextId++, name};

        if (static_cast<int>(confirmed.size()) < capacity) {
            confirmed.push_back(passenger);

            cout << "Ticket confirmed!\n";
            cout << "Passenger ID: " << passenger.id << '\n';
        } else {
            waiting.push(passenger);

            cout << "Train is full. Added to waiting list.\n";
            cout << "Passenger ID: " << passenger.id << '\n';
            cout << "Waiting position: " << waiting.size() << '\n';
        }
    }

    void promoteWaitingPassenger() {
        if (waiting.empty()) {
            return;
        }

        Passenger passenger = waiting.front();
        waiting.pop();

        confirmed.push_back(passenger);

        cout << "Waiting-list passenger promoted: "
             << passenger.name
             << " (ID: " << passenger.id << ")\n";
    }

    void cancelTicket(int id) {
        for (size_t i = 0; i < confirmed.size(); ++i) {
            if (confirmed[i].id == id) {
                cout << "Cancelled confirmed ticket for "
                     << confirmed[i].name << ".\n";

                confirmed.erase(confirmed.begin() + i);

                promoteWaitingPassenger();
                return;
            }
        }

        // If not confirmed, check the waiting queue.
        queue<Passenger> temp;
        bool found = false;

        while (!waiting.empty()) {
            Passenger passenger = waiting.front();
            waiting.pop();

            if (passenger.id == id && !found) {
                found = true;
                cout << "Removed passenger "
                     << passenger.name
                     << " from waiting list.\n";
            } else {
                temp.push(passenger);
            }
        }

        waiting = temp;

        if (!found) {
            cout << "Passenger ID not found.\n";
        }
    }

    void displayConfirmed() const {
        cout << "\n--- Confirmed Reservations ---\n";

        if (confirmed.empty()) {
            cout << "No confirmed reservations.\n";
            return;
        }

        for (const Passenger& passenger : confirmed) {
            cout << "ID: " << passenger.id
                 << " | Name: " << passenger.name << '\n';
        }
    }

    void displayWaiting() const {
        cout << "\n--- Waiting List (FIFO) ---\n";

        if (waiting.empty()) {
            cout << "No passengers waiting.\n";
            return;
        }

        queue<Passenger> temp = waiting;
        int position = 1;

        while (!temp.empty()) {
            Passenger passenger = temp.front();
            temp.pop();

            cout << "Position: " << position++
                 << " | ID: " << passenger.id
                 << " | Name: " << passenger.name << '\n';
        }
    }

    void searchPassenger(int id) const {
        for (size_t i = 0; i < confirmed.size(); ++i) {
            if (confirmed[i].id == id) {
                cout << "Passenger: " << confirmed[i].name
                     << " | Status: Confirmed"
                     << " | Seat number: " << i + 1 << '\n';
                return;
            }
        }

        queue<Passenger> temp = waiting;
        int position = 1;

        while (!temp.empty()) {
            Passenger passenger = temp.front();
            temp.pop();

            if (passenger.id == id) {
                cout << "Passenger: " << passenger.name
                     << " | Status: Waiting"
                     << " | Position: " << position << '\n';
                return;
            }

            ++position;
        }

        cout << "Passenger ID not found.\n";
    }

    void showStatistics() const {
        cout << "\n--- Railway Statistics ---\n";
        cout << "Train capacity: " << capacity << '\n';
        cout << "Confirmed tickets: " << confirmed.size() << '\n';
        cout << "Available seats: "
             << capacity - confirmed.size() << '\n';
        cout << "Waiting passengers: " << waiting.size() << '\n';
    }
};

int main() {
    int capacity;

    cout << "Enter train seat capacity: ";

    if (!(cin >> capacity) || capacity <= 0) {
        cout << "Invalid capacity.\n";
        return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    RailwayReservation railway(capacity);
    int choice;

    do {
        cout << "\n===== RAILWAY RESERVATION SYSTEM =====\n";
        cout << "1. Book ticket\n";
        cout << "2. Cancel ticket\n";
        cout << "3. Display confirmed reservations\n";
        cout << "4. Display waiting list\n";
        cout << "5. Search passenger\n";
        cout << "6. Show statistics\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            cout << "Invalid input.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            string name;

            cout << "Enter passenger name: ";
            getline(cin, name);

            railway.bookTicket(name);
            break;
        }

        case 2: {
            int id;

            cout << "Enter passenger ID to cancel: ";

            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                cout << "Invalid passenger ID.\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            railway.cancelTicket(id);
            break;
        }

        case 3:
            railway.displayConfirmed();
            break;

        case 4:
            railway.displayWaiting();
            break;

        case 5: {
            int id;

            cout << "Enter passenger ID to search: ";

            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                cout << "Invalid passenger ID.\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            railway.searchPassenger(id);
            break;
        }

        case 6:
            railway.showStatistics();
            break;

        case 0:
            cout << "Exiting reservation system.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
