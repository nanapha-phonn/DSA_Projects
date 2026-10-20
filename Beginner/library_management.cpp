
#include <iostream>
#include <string>
using namespace std;

int main() {
    string books[100];
    bool borrowed[100] = {false};
    int totalBooks = 0;
    int choice;

    while (true) {
        cout << "\n=== Library Management System ===\n";
        cout << "1. Add Book\n";
        cout << "2. Show All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            if (totalBooks >= 100) {
                cout << "Library is full!\n";
            }
            else {
                cout << "Enter book name: ";
                cin >> ws;
                getline(cin, books[totalBooks]);

                borrowed[totalBooks] = false;
                totalBooks++;

                cout << "Book added successfully!\n";
            }
        }
        else if (choice == 2) {
            if (totalBooks == 0) {
                cout << "No books available.\n";
            }
            else {
                cout << "\n--- Book List ---\n";

                for (int i = 0; i < totalBooks; i++) {
                    cout << i + 1 << ". " << books[i];

                    if (borrowed[i]) {
                        cout << " (Borrowed)";
                    }
                    else {
                        cout << " (Available)";
                    }

                    cout << endl;
                }
            }
        }
        else if (choice == 3) {
            string searchName;
            bool found = false;

            cout << "Enter book name to search: ";
            cin >> ws;
            getline(cin, searchName);

            for (int i = 0; i < totalBooks; i++) {
                if (books[i] == searchName) {
                    cout << "Book found: " << books[i] << endl;

                    if (borrowed[i]) {
                        cout << "Status: Borrowed\n";
                    }
                    else {
                        cout << "Status: Available\n";
                    }

                    found = true;
                }
            }

            if (!found) {
                cout << "Book not found.\n";
            }
        }
        else if (choice == 4) {
            int bookNumber;

            cout << "Enter book number to borrow: ";
            cin >> bookNumber;

            if (bookNumber < 1 || bookNumber > totalBooks) {
                cout << "Invalid book number.\n";
            }
            else if (borrowed[bookNumber - 1]) {
                cout << "This book is already borrowed.\n";
            }
            else {
                borrowed[bookNumber - 1] = true;
                cout << "You borrowed: "
                     << books[bookNumber - 1] << endl;
            }
        }
        else if (choice == 5) {
            int bookNumber;

            cout << "Enter book number to return: ";
            cin >> bookNumber;

            if (bookNumber < 1 || bookNumber > totalBooks) {
                cout << "Invalid book number.\n";
            }
            else if (!borrowed[bookNumber - 1]) {
                cout << "This book has not been borrowed.\n";
            }
            else {
                borrowed[bookNumber - 1] = false;
                cout << "Book returned successfully!\n";
            }
        }
        else if (choice == 6) {
            cout << "Library system closed.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
