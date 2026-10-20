
#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    unordered_set<string> dictionary = {
        "hello", "world", "computer", "program",
        "student", "school", "coding", "friend",
        "apple", "book", "happy", "learn"
    };

    string word;

    cout << "=== Simple Spell Checker ===\n";
    cout << "Enter a word: ";
    cin >> word;

    // Convert the word to lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    // Check if the word exists in the dictionary
    if (dictionary.find(word) != dictionary.end()) {
        cout << "Correct spelling!\n";
    }
    else {
        cout << "Word not found. Check your spelling.\n";
    }

    return 0;
}
