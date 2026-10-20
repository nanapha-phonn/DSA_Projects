
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    vector<string> names;
    vector<int> scores;

    int choice;

    while (true) {
        cout << "\n=== Leaderboard Ranking System ===\n";
        cout << "1. Add Player\n";
        cout << "2. Show Leaderboard\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int score;

            cout << "Enter player name: ";
            cin >> ws;
            getline(cin, name);

            cout << "Enter player score: ";
            cin >> score;

            names.push_back(name);
            scores.push_back(score);

            cout << "Player added successfully!\n";
        }
        else if (choice == 2) {
            if (names.empty()) {
                cout << "No players in the leaderboard.\n";
            }
            else {
                // Sort players by score from highest to lowest
                for (int i = 0; i < scores.size() - 1; i++) {
                    for (int j = 0; j < scores.size() - i - 1; j++) {
                        if (scores[j] < scores[j + 1]) {
                            swap(scores[j], scores[j + 1]);
                            swap(names[j], names[j + 1]);
                        }
                    }
                }

                cout << "\n--- Leaderboard ---\n";

                for (int i = 0; i < names.size(); i++) {
                    cout << i + 1 << ". "
                         << names[i] << " - "
                         << scores[i] << " points\n";
                }
            }
        }
        else if (choice == 3) {
            cout << "Program closed.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
