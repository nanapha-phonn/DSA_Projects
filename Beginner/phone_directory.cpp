
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    unordered_map<string, string> contacts;

    int choice;
    string name, phone;

    while (true) {
        cout << "\n=== Phone Directory ===\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Show All Contacts\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter name: ";
            cin >> ws;
            getline(cin, name);

            cout << "Enter phone number: ";
            getline(cin, phone);

            contacts[name] = phone;

            cout << "Contact saved successfully!\n";
        }
        else if (choice == 2) {
            cout << "Enter name to search: ";
            cin >> ws;
            getline(cin, name);

            if (contacts.find(name) != contacts.end()) {
                cout << "Name: " << name << endl;
                cout << "Phone: " << contacts[name] << endl;
            }
            else {
                cout << "Contact not found.\n";
            }
        }
        else if (choice == 3) {
            if (contacts.empty()) {
                cout << "No contacts available.\n";
            }
            else {
                cout << "\n--- All Contacts ---\n";

                for (auto contact : contacts) {
                    cout << "Name: " << contact.first
                         << " | Phone: " << contact.second
                         << endl;
                }
            }
        }
        else if (choice == 4) {
            cout << "Enter name to delete: ";
            cin >> ws;
            getline(cin, name);

            if (contacts.erase(name) > 0) {
                cout << "Contact deleted successfully!\n";
            }
            else {
                cout << "Contact not found.\n";
            }
        }
        else if (choice == 5) {
            cout << "Phone directory closed.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
