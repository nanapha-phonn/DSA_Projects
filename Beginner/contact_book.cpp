#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Contact {
    string name;
    string phone;  // Keep phone numbers as strings to preserve leading zeros and '+'.
};

struct Node {
    Contact data;
    Node* prev = nullptr;
    Node* next = nullptr;

    explicit Node(const Contact& contact) : data(contact) {}
};

class ContactBook {
private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    size_t size_ = 0;
    const string filename_ = "contactbook.txt";

    static string trim(const string& value) {
        const size_t first = value.find_first_not_of(" \t\r\n");
        if (first == string::npos) return "";
        const size_t last = value.find_last_not_of(" \t\r\n");
        return value.substr(first, last - first + 1);
    }

    static string normalizeName(const string& name) {
        string result = trim(name);
        transform(result.begin(), result.end(), result.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });
        return result;
    }

    static bool validPhone(const string& phone) {
        if (phone.empty()) return false;

        size_t digits = 0;
        for (size_t i = 0; i < phone.size(); ++i) {
            const unsigned char c = static_cast<unsigned char>(phone[i]);
            if (isdigit(c)) {
                ++digits;
            } else if (c == '+' && i == 0) {
                // A leading plus sign is allowed.
            } else if (c == ' ' || c == '-' || c == '(' || c == ')') {
                // Common phone-number formatting characters are allowed.
            } else {
                return false;
            }
        }
        return digits >= 3;
    }

    static string readNonEmptyLine(const string& prompt) {
        while (true) {
            cout << prompt;
            string value;
            if (!getline(cin, value)) return "";
            value = trim(value);
            if (!value.empty()) return value;
            cout << "Input cannot be empty. Please try again.\n";
        }
    }

    static int readChoice(const string& prompt, int minimum, int maximum) {
        while (true) {
            cout << prompt;
            string line;
            if (!getline(cin, line)) return -1;

            try {
                size_t used = 0;
                int value = stoi(line, &used);
                if (used == line.size() && value >= minimum && value <= maximum) {
                    return value;
                }
            } catch (...) {
                // Invalid input is handled below.
            }
            cout << "Invalid choice. Enter a number from "
                 << minimum << " to " << maximum << ".\n";
        }
    }

    static string readPhone(const string& prompt) {
        while (true) {
            cout << prompt;
            string phone;
            if (!getline(cin, phone)) return "";
            phone = trim(phone);
            if (validPhone(phone)) return phone;
            cout << "Invalid phone number. Use digits and optional +, spaces, -, ( or ).\n";
        }
    }

    Node* findByName(const string& name) const {
        const string target = normalizeName(name);
        for (Node* current = head_; current != nullptr; current = current->next) {
            if (normalizeName(current->data.name) == target) return current;
        }
        return nullptr;
    }

    Node* findByPhone(const string& phone) const {
        for (Node* current = head_; current != nullptr; current = current->next) {
            if (current->data.phone == phone) return current;
        }
        return nullptr;
    }

    bool phoneExists(const string& phone, const Node* except = nullptr) const {
        for (Node* current = head_; current != nullptr; current = current->next) {
            if (current != except && current->data.phone == phone) return true;
        }
        return false;
    }

    void append(const Contact& contact) {
        Node* node = new Node(contact);
        if (tail_ == nullptr) {
            head_ = tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    void unlink(Node* node) {
        if (node == nullptr) return;

        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;
        }

        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;
        }

        delete node;
        --size_;
    }

    void clearList() {
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

public:
    ContactBook() = default;

    ~ContactBook() {
        clearList();
    }

    ContactBook(const ContactBook&) = delete;
    ContactBook& operator=(const ContactBook&) = delete;

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return head_ == nullptr;
    }

    bool saveToFile() const {
        const string temporaryFile = filename_ + ".tmp";
        ofstream out(temporaryFile, ios::trunc);
        if (!out) {
            cerr << "Error: cannot open " << temporaryFile << " for writing.\n";
            return false;
        }

        // Format: one contact per line; name and phone are tab-separated.
        // Names containing tabs/newlines are rejected by input validation.
        for (Node* current = head_; current != nullptr; current = current->next) {
            out << current->data.name << '\t' << current->data.phone << '\n';
            if (!out) {
                cerr << "Error while writing contacts to file.\n";
                return false;
            }
        }
        out.close();
        if (!out) {
            cerr << "Error while closing the contacts file.\n";
            return false;
        }

        if (rename(temporaryFile.c_str(), filename_.c_str()) != 0) {
            // Fallback for platforms where rename won't replace an existing file.
            remove(filename_.c_str());
            if (rename(temporaryFile.c_str(), filename_.c_str()) != 0) {
                cerr << "Error: could not replace " << filename_ << ".\n";
                return false;
            }
        }
        return true;
    }

    void loadFromFile() {
        ifstream in(filename_);
        if (!in) {
            // Missing file is normal on the first run.
            return;
        }

        clearList();
        string line;
        size_t lineNumber = 0;

        while (getline(in, line)) {
            ++lineNumber;
            const size_t separator = line.find('\t');
            if (separator == string::npos) {
                cerr << "Warning: skipping malformed line " << lineNumber << ".\n";
                continue;
            }

            Contact contact{trim(line.substr(0, separator)),
                            trim(line.substr(separator + 1))};

            if (contact.name.empty() || !validPhone(contact.phone) ||
                findByName(contact.name) != nullptr ||
                phoneExists(contact.phone)) {
                cerr << "Warning: skipping invalid or duplicate contact on line "
                     << lineNumber << ".\n";
                continue;
            }

            append(contact);
        }

        if (in.bad()) {
            cerr << "Error while reading " << filename_ << ".\n";
        }
    }

    void addContact() {
        string name = readNonEmptyLine("Name: ");
        if (name.empty()) return;
        if (name.find('\t') != string::npos) {
            cout << "Name cannot contain a tab character.\n";
            return;
        }
        if (findByName(name) != nullptr) {
            cout << "A contact with that name already exists.\n";
            return;
        }

        string phone = readPhone("Phone number: ");
        if (phone.empty()) return;
        if (phoneExists(phone)) {
            cout << "That phone number is already saved.\n";
            return;
        }

        append({name, phone});
        if (saveToFile()) cout << "Contact added and saved.\n";
        else cout << "Contact added in memory, but saving failed.\n";
    }

    void displayContacts() const {
        if (empty()) {
            cout << "Contact book is empty.\n";
            return;
        }

        cout << "\n" << left << setw(4) << "#"
             << setw(30) << "Name" << "Phone\n";
        cout << string(55, '-') << '\n';

        size_t index = 1;
        for (Node* current = head_; current != nullptr; current = current->next) {
            cout << left << setw(4) << index++
                 << setw(30) << current->data.name
                 << current->data.phone << '\n';
        }
        cout << "Total contacts: " << size_ << '\n';
    }

    void searchContact() const {
        if (empty()) {
            cout << "Contact book is empty.\n";
            return;
        }

        cout << "Search by: 1. Name  2. Phone number\n";
        int choice = readChoice("Choose: ", 1, 2);
        if (choice == -1) return;

        Node* result = nullptr;
        if (choice == 1) {
            string name = readNonEmptyLine("Name to search: ");
            if (name.empty()) return;
            result = findByName(name);
        } else {
            string phone = readPhone("Phone number to search: ");
            if (phone.empty()) return;
            result = findByPhone(phone);
        }

        if (result == nullptr) {
            cout << "Contact not found.\n";
        } else {
            cout << "\nName : " << result->data.name
                 << "\nPhone: " << result->data.phone << '\n';
        }
    }

    void editContact() {
        if (empty()) {
            cout << "Contact book is empty.\n";
            return;
        }

        cout << "Find contact by: 1. Name  2. Phone number\n";
        int choice = readChoice("Choose: ", 1, 2);
        if (choice == -1) return;

        Node* target = nullptr;
        if (choice == 1) {
            string name = readNonEmptyLine("Current name: ");
            if (name.empty()) return;
            target = findByName(name);
        } else {
            string phone = readPhone("Current phone number: ");
            if (phone.empty()) return;
            target = findByPhone(phone);
        }

        if (target == nullptr) {
            cout << "Contact not found.\n";
            return;
        }

        cout << "Current contact: " << target->data.name
             << " | " << target->data.phone << '\n';

        string newName = readNonEmptyLine("New name: ");
        if (newName.empty()) return;
        if (newName.find('\t') != string::npos) {
            cout << "Name cannot contain a tab character.\n";
            return;
        }

        Node* sameName = findByName(newName);
        if (sameName != nullptr && sameName != target) {
            cout << "Another contact already uses that name.\n";
            return;
        }

        string newPhone = readPhone("New phone number: ");
        if (newPhone.empty()) return;
        if (phoneExists(newPhone, target)) {
            cout << "Another contact already uses that phone number.\n";
            return;
        }

        target->data.name = newName;
        target->data.phone = newPhone;

        if (saveToFile()) cout << "Contact updated and saved.\n";
        else cout << "Contact updated in memory, but saving failed.\n";
    }

    void deleteContact() {
        if (empty()) {
            cout << "Contact book is empty.\n";
            return;
        }

        cout << "Find contact by: 1. Name  2. Phone number\n";
        int choice = readChoice("Choose: ", 1, 2);
        if (choice == -1) return;

        Node* target = nullptr;
        if (choice == 1) {
            string name = readNonEmptyLine("Name to delete: ");
            if (name.empty()) return;
            target = findByName(name);
        } else {
            string phone = readPhone("Phone number to delete: ");
            if (phone.empty()) return;
            target = findByPhone(phone);
        }

        if (target == nullptr) {
            cout << "Contact not found.\n";
            return;
        }

        cout << "Delete " << target->data.name << " ("
             << target->data.phone << ")?\n";
        int confirm = readChoice("1. Confirm  2. Cancel: ", 1, 2);
        if (confirm != 1) {
            cout << "Deletion cancelled.\n";
            return;
        }

        unlink(target);
        if (saveToFile()) cout << "Contact deleted and saved.\n";
        else cout << "Contact deleted in memory, but saving failed.\n";
    }

    void deleteAllContacts() {
        if (empty()) {
            cout << "Contact book is already empty.\n";
            return;
        }

        int confirm = readChoice("Delete ALL contacts? 1. Confirm  2. Cancel: ", 1, 2);
        if (confirm != 1) {
            cout << "Deletion cancelled.\n";
            return;
        }

        clearList();
        if (saveToFile()) cout << "All contacts deleted and file cleared.\n";
        else cout << "Contacts cleared in memory, but saving failed.\n";
    }

    void sortContacts() {
        if (size_ < 2) {
            cout << "At least two contacts are needed to sort.\n";
            return;
        }

        // Bubble sort swaps contact data, leaving node links unchanged.
        bool swapped;
        do {
            swapped = false;
            for (Node* current = head_; current->next != nullptr;
                 current = current->next) {
                if (normalizeName(current->data.name) >
                    normalizeName(current->next->data.name)) {
                    swap(current->data, current->next->data);
                    swapped = true;
                }
            }
        } while (swapped);

        if (saveToFile()) cout << "Contacts sorted alphabetically and saved.\n";
        else cout << "Contacts sorted in memory, but saving failed.\n";
    }

    void run() {
        loadFromFile();

        while (true) {
            cout << "\n========== CONTACT BOOK ==========\n"
                 << "1. Add contact\n"
                 << "2. Display contacts\n"
                 << "3. Search contact\n"
                 << "4. Edit contact\n"
                 << "5. Delete contact\n"
                 << "6. Delete all contacts\n"
                 << "7. Sort contacts by name\n"
                 << "8. Count contacts\n"
                 << "9. Save contacts\n"
                 << "0. Exit\n";

            int choice = readChoice("Choose an option: ", 0, 9);
            if (choice == -1) {
                cout << "\nInput closed. Exiting.\n";
                break;
            }

            switch (choice) {
                case 1: addContact(); break;
                case 2: displayContacts(); break;
                case 3: searchContact(); break;
                case 4: editContact(); break;
                case 5: deleteContact(); break;
                case 6: deleteAllContacts(); break;
                case 7: sortContacts(); break;
                case 8: cout << "Total contacts: " << size_ << '\n'; break;
                case 9:
                    cout << (saveToFile() ? "Contacts saved.\n"
                                          : "Saving failed.\n");
                    break;
                case 0:
                    saveToFile();
                    cout << "Goodbye.\n";
                    return;
            }
        }
    }
};

int main() {
    ContactBook book;
    book.run();
    return 0;
}
