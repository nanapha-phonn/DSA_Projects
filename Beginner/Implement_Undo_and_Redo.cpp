#include <iostream>
#include <stack>
#include <string>
#include <limits>

using namespace std;

class TextEditor {
private:
    string document_;
    stack<char> undoStack_;
    stack<char> redoStack_;

    void clearStack(stack<char>& values) {
        while (!values.empty()) {
            values.pop();
        }
    }

public:
    // Add one character. A new edit invalidates the redo history.
    void append(char ch) {
        document_.push_back(ch);
        undoStack_.push(ch);
        clearStack(redoStack_);
    }

    // Remove the last character and save it for redo.
    bool undo() {
        if (undoStack_.empty()) {
            return false;
        }

        char last = undoStack_.top();
        undoStack_.pop();
        document_.pop_back();
        redoStack_.push(last);
        return true;
    }

    // Restore the last character removed by undo.
    bool redo() {
        if (redoStack_.empty()) {
            return false;
        }

        char ch = redoStack_.top();
        redoStack_.pop();
        document_.push_back(ch);
        undoStack_.push(ch);
        return true;
    }

    // Return the current document without changing it.
    const string& read() const {
        return document_;
    }

    bool empty() const {
        return document_.empty();
    }

    void clear() {
        document_.clear();
        clearStack(undoStack_);
        clearStack(redoStack_);
    }
};

int main() {
    TextEditor editor;
    int choice = 0;

    while (true) {
        cout << "\n===== TEXT EDITOR =====\n"
             << "Document: \"" << editor.read() << "\"\n"
             << "1. Append character\n"
             << "2. Undo\n"
             << "3. Redo\n"
             << "4. Read document\n"
             << "5. Clear document\n"
             << "0. Exit\n"
             << "Choose an option: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Exiting.\n";
            break;
        }

        if (choice == 0) {
            cout << "Goodbye.\n";
            break;
        }

        switch (choice) {
            case 1: {
                cout << "Enter one character: ";
                char ch;
                if (!(cin >> ch)) {
                    cout << "Invalid character input.\n";
                    return 1;
                }
                editor.append(ch);
                cout << "Character appended.\n";
                break;
            }

            case 2:
                if (editor.undo()) {
                    cout << "Undo successful.\n";
                } else {
                    cout << "Nothing to undo; document is empty.\n";
                }
                break;

            case 3:
                if (editor.redo()) {
                    cout << "Redo successful.\n";
                } else {
                    cout << "Nothing to redo.\n";
                }
                break;

            case 4:
                cout << "Current document: " << editor.read() << '\n';
                break;

            case 5:
                editor.clear();
                cout << "Document and history cleared.\n";
                break;

            default:
                cout << "Invalid choice. Choose 0 to 5.\n";
        }
    }

    return 0;
}
