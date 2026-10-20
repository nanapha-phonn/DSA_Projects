
#include <iostream>
#include <string>
using namespace std;

struct Account {
    int accountNumber;
    string name;
    double balance;
    Account* next;
};

Account* head = NULL;

// Create a new bank account
void createAccount() {
    Account* newAccount = new Account;

    cout << "Enter account number: ";
    cin >> newAccount->accountNumber;

    // Check for duplicate account numbers
    Account* current = head;

    while (current != NULL) {
        if (current->accountNumber == newAccount->accountNumber) {
            cout << "Account number already exists!\n";
            delete newAccount;
            return;
        }

        current = current->next;
    }

    cout << "Enter account holder name: ";
    cin >> ws;
    getline(cin, newAccount->name);

    cout << "Enter starting balance: ";
    cin >> newAccount->balance;

    if (newAccount->balance < 0) {
        cout << "Balance cannot be negative!\n";
        delete newAccount;
        return;
    }

    newAccount->next = NULL;

    if (head == NULL) {
        head = newAccount;
    }
    else {
        Account* current = head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newAccount;
    }

    cout << "Account created successfully!\n";
}

// Display all bank accounts
void showAccounts() {
    Account* current = head;

    if (current == NULL) {
        cout << "No accounts available.\n";
        return;
    }

    cout << "\n=== Bank Accounts ===\n";

    while (current != NULL) {
        cout << "Account Number: " << current->accountNumber << endl;
        cout << "Name: " << current->name << endl;
        cout << "Balance: $" << current->balance << endl;
        cout << "----------------------\n";

        current = current->next;
    }
}

// Search for an account
Account* searchAccount(int number) {
    Account* current = head;

    while (current != NULL) {
        if (current->accountNumber == number) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

// Deposit money
void depositMoney() {
    int number;
    double amount;

    cout << "Enter account number: ";
    cin >> number;

    Account* account = searchAccount(number);

    if (account == NULL) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter deposit amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Amount must be greater than zero!\n";
        return;
    }

    account->balance = account->balance + amount;

    cout << "Deposit successful!\n";
    cout << "New balance: $" << account->balance << endl;
}

// Withdraw money
void withdrawMoney() {
    int number;
    double amount;

    cout << "Enter account number: ";
    cin >> number;

    Account* account = searchAccount(number);

    if (account == NULL) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter withdrawal amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Amount must be greater than zero!\n";
    }
    else if (amount > account->balance) {
        cout << "Not enough money in the account!\n";
    }
    else {
        account->balance = account->balance - amount;

        cout << "Withdrawal successful!\n";
        cout << "Remaining balance: $" << account->balance << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n=== Bank Account System ===\n";
        cout << "1. Create Account\n";
        cout << "2. Show All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            createAccount();
        }
        else if (choice == 2) {
            showAccounts();
        }
        else if (choice == 3) {
            int number;

            cout << "Enter account number: ";
            cin >> number;

            Account* account = searchAccount(number);

            if (account != NULL) {
                cout << "Account Number: " << account->accountNumber << endl;
                cout << "Name: " << account->name << endl;
                cout << "Balance: $" << account->balance << endl;
            }
            else {
                cout << "Account not found!\n";
            }
        }
        else if (choice == 4) {
            depositMoney();
        }
        else if (choice == 5) {
            withdrawMoney();
        }
        else if (choice == 6) {
            cout << "Bank system closed.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    // Free memory before closing
    while (head != NULL) {
        Account* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
