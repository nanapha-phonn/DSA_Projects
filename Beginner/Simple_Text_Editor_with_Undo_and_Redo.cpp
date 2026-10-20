
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string text = "";
    stack<string> undoStack;
    stack<string> redoStack;

    int choice;
    string newText;

    while (true) {
        cout << "\n=== Simple Text Editor ===\n";
        cout << "1. Write Text\n";
        cout << "2. Undo\n";
        cout << "3. Redo\n";
        cout << "4. Show Text\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter new text: ";
            cin >> ws;
            getline(cin, newText);

            // Save the current text before changing it
            undoStack.push(text);

            text = newText;

            // Clear redo history after a new change
            while (!redoStack.empty()) {
                redoStack.pop();
            }

            cout << "Text updated successfully!\n";
        }
        else if (choice == 2) {
            if (undoStack.empty()) {
                cout << "Nothing to undo.\n";
            }
            else {
                // Save current text for redo
                redoStack.push(text);

                text = undoStack.top();
                undoStack.pop();

                cout << "Undo successful!\n";
            }
        }
        else if (choice == 3) {
            if (redoStack.empty()) {
                cout << "Nothing to redo.\n";
            }
            else {
                // Save current text for undo
                undoStack.push(text);

                text = redoStack.top();
                redoStack.pop();

                cout << "Redo successful!\n";
            }
        }
        else if (choice == 4) {
            cout << "\nCurrent Text: " << text << endl;
        }
        else if (choice == 5) {
            cout << "Text editor closed.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
