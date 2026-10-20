
#include <iostream>
#include <stack>
#include <string>
#include <limits>

using namespace std;

class BrowserHistory {
private:
    stack<string> backStack;
    stack<string> forwardStack;
    string currentPage = "about:blank";

public:
    void visit(const string& url) {
        if (url.empty()) {
            cout << "URL cannot be empty.\n";
            return;
        }

        if (currentPage != "about:blank") {
            backStack.push(currentPage);
        }

        currentPage = url;

        // A new visit invalidates forward history.
        while (!forwardStack.empty()) {
            forwardStack.pop();
        }

        cout << "Visited: " << currentPage << '\n';
    }

    void goBack() {
        if (backStack.empty()) {
            cout << "No previous page available.\n";
            return;
        }

        forwardStack.push(currentPage);
        currentPage = backStack.top();
        backStack.pop();

        cout << "Current page: " << currentPage << '\n';
    }

    void goForward() {
        if (forwardStack.empty()) {
            cout << "No next page available.\n";
            return;
        }

        backStack.push(currentPage);
        currentPage = forwardStack.top();
        forwardStack.pop();

        cout << "Current page: " << currentPage << '\n';
    }

    void showCurrentPage() const {
        cout << "Current page: " << currentPage << '\n';
    }

    void showBackHistory() const {
        if (backStack.empty()) {
            cout << "No back history.\n";
            return;
        }

        stack<string> temp = backStack;

        cout << "\n--- Back History (Newest First) ---\n";

        while (!temp.empty()) {
            cout << temp.top() << '\n';
            temp.pop();
        }
    }

    void showForwardHistory() const {
        if (forwardStack.empty()) {
            cout << "No forward history.\n";
            return;
        }

        stack<string> temp = forwardStack;

        cout << "\n--- Forward History (Next First) ---\n";

        while (!temp.empty()) {
            cout << temp.top() << '\n';
            temp.pop();
        }
    }

    void clearHistory() {
        while (!backStack.empty()) {
            backStack.pop();
        }

        while (!forwardStack.empty()) {
            forwardStack.pop();
        }

        currentPage = "about:blank";

        cout << "Browser history cleared.\n";
    }
};

int main() {
    BrowserHistory browser;
    int choice;

    do {
        cout << "\n===== BROWSER HISTORY MANAGER =====\n";
        cout << "1. Visit website\n";
        cout << "2. Go back\n";
        cout << "3. Go forward\n";
        cout << "4. Show current page\n";
        cout << "5. Show back history\n";
        cout << "6. Show forward history\n";
        cout << "7. Clear history\n";
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

        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );

        switch (choice) {
        case 1: {
            string url;

            cout << "Enter website URL: ";
            getline(cin, url);

            browser.visit(url);
            break;
        }

        case 2:
            browser.goBack();
            break;

        case 3:
            browser.goForward();
            break;

        case 4:
            browser.showCurrentPage();
            break;

        case 5:
            browser.showBackHistory();
            break;

        case 6:
            browser.showForwardHistory();
            break;

        case 7:
            browser.clearHistory();
            break;

        case 0:
            cout << "Exiting browser history manager.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
