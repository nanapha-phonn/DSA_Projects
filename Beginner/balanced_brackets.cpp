
#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isOpeningBracket(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

bool isClosingBracket(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

bool isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

bool isBalanced(const string& expression) {
    stack<char> brackets;

    for (char ch : expression) {
        if (isOpeningBracket(ch)) {
            brackets.push(ch);
        }
        else if (isClosingBracket(ch)) {
            // No opening bracket to match this closing bracket.
            if (brackets.empty()) {
                return false;
            }

            char top = brackets.top();

            if (!isMatchingPair(top, ch)) {
                return false;
            }

            brackets.pop();
        }
    }

    // Any remaining opening brackets are unmatched.
    return brackets.empty();
}

int main() {
    string expression;

    cout << "===== BALANCED BRACKETS VALIDATOR =====\n";
    cout << "Enter an expression: ";
    getline(cin, expression);

    if (isBalanced(expression)) {
        cout << "Result: Balanced brackets.\n";
    } else {
        cout << "Result: Unbalanced brackets.\n";
    }

    return 0;
}
