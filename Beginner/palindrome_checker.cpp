
#include <cctype>
#include <deque>
#include <iostream>
#include <string>

using namespace std;

// Remove spaces and punctuation, and convert to lowercase.
string normalizeText(const string& text) {
    string normalized;

    for (unsigned char ch : text) {
        if (isalnum(ch)) {
            normalized += static_cast<char>(tolower(ch));
        }
    }

    return normalized;
}

// Check whether the text is a palindrome using a deque.
bool isPalindrome(const string& text) {
    deque<char> characters;

    for (char ch : text) {
        characters.push_back(ch);
    }

    while (characters.size() > 1) {
        if (characters.front() != characters.back()) {
            return false;
        }

        characters.pop_front();
        characters.pop_back();
    }

    return true;
}

int main() {
    string input;

    cout << "=== Palindrome Checker ===\n";
    cout << "Enter a word or phrase: ";

    getline(cin, input);

    string normalized = normalizeText(input);

    if (normalized.empty()) {
        cout << "Error: Please enter at least one letter or digit.\n";
        return 1;
    }

    cout << "\nOriginal text: " << input << '\n';

    if (isPalindrome(normalized)) {
        cout << "Result: Palindrome\n";
        cout << "The text reads the same forward and backward.\n";
    } else {
        cout << "Result: Not a palindrome\n";
        cout << "The text differs when reversed.\n";
    }

    return 0;
}
