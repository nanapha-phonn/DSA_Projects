
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct PrintJob {
    int id;
    string filename;
    int pages;
};

class PrinterQueue {
private:
    queue<PrintJob> pendingJobs;
    vector<PrintJob> completedJobs;
    int nextId = 1;

public:
    void addJob(const string& filename, int pages) {
        if (filename.empty() || pages <= 0) {
            cout << "Invalid filename or page count.\n";
            return;
        }

        PrintJob job{nextId++, filename, pages};
        pendingJobs.push(job);

        cout << "Job added successfully. ID: "
             << job.id << '\n';
    }

    void printNextJob() {
        if (pendingJobs.empty()) {
            cout << "No jobs waiting to print.\n";
            return;
        }

        PrintJob job = pendingJobs.front();
        pendingJobs.pop();

        cout << "\nPrinting document...\n";
        cout << "Job ID: " << job.id << '\n';
        cout << "Filename: " << job.filename << '\n';
        cout << "Pages: " << job.pages << '\n';

        completedJobs.push_back(job);

        cout << "Printing completed.\n";
    }

    void displayQueue() const {
        if (pendingJobs.empty()) {
            cout << "The print queue is empty.\n";
            return;
        }

        queue<PrintJob> temp = pendingJobs;

        cout << "\n--- Pending Print Jobs ---\n";

        while (!temp.empty()) {
            PrintJob job = temp.front();
            temp.pop();

            cout << "ID: " << job.id
                 << " | File: " << job.filename
                 << " | Pages: " << job.pages << '\n';
        }
    }

    void viewNextJob() const {
        if (pendingJobs.empty()) {
            cout << "No next job available.\n";
            return;
        }

        const PrintJob& job = pendingJobs.front();

        cout << "Next job: " << job.filename
             << " (ID: " << job.id << ")\n";
    }

    void cancelJob(int id) {
        queue<PrintJob> temp;
        bool found = false;

        while (!pendingJobs.empty()) {
            PrintJob job = pendingJobs.front();
            pendingJobs.pop();

            if (job.id == id && !found) {
                found = true;
                continue;
            }

            temp.push(job);
        }

        pendingJobs = temp;

        if (found) {
            cout << "Job " << id << " cancelled.\n";
        } else {
            cout << "Pending job ID not found.\n";
        }
    }

    void displayCompletedJobs() const {
        if (completedJobs.empty()) {
            cout << "No completed jobs yet.\n";
            return;
        }

        cout << "\n--- Completed Print Jobs ---\n";

        for (const PrintJob& job : completedJobs) {
            cout << "ID: " << job.id
                 << " | File: " << job.filename
                 << " | Pages: " << job.pages << '\n';
        }
    }

    void displayStatistics() const {
        cout << "\n--- Printer Statistics ---\n";
        cout << "Pending jobs: " << pendingJobs.size() << '\n';
        cout << "Completed jobs: " << completedJobs.size() << '\n';

        int totalPages = 0;

        for (const PrintJob& job : completedJobs) {
            totalPages += job.pages;
        }

        cout << "Pages printed: " << totalPages << '\n';
    }
};

int main() {
    PrinterQueue printer;
    int choice;

    do {
        cout << "\n===== PRINTER QUEUE SYSTEM =====\n";
        cout << "1. Add print job\n";
        cout << "2. Print next job\n";
        cout << "3. View pending queue\n";
        cout << "4. View next job\n";
        cout << "5. Cancel pending job\n";
        cout << "6. View completed jobs\n";
        cout << "7. Show statistics\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            string filename;
            int pages;

            cout << "Enter filename: ";
            getline(cin, filename);

            cout << "Enter number of pages: ";

            if (!(cin >> pages)) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                cout << "Invalid page count.\n";
                break;
            }

            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );

            printer.addJob(filename, pages);
            break;
        }

        case 2:
            printer.printNextJob();
            break;

        case 3:
            printer.displayQueue();
            break;

        case 4:
            printer.viewNextJob();
            break;

        case 5: {
            int id;
            cout << "Enter job ID to cancel: ";

            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                cout << "Invalid job ID.\n";
                break;
            }

            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );

            printer.cancelJob(id);
            break;
        }

        case 6:
            printer.displayCompletedJobs();
            break;

        case 7:
            printer.displayStatistics();
            break;

        case 0:
            cout << "Exiting printer queue system.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
