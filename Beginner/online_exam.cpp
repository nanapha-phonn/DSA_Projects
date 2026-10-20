
#include <iostream>
#include <string>
using namespace std;

int main() {
    string questions[5] = {
        "1. What does CPU stand for?",
        "2. Which language is used for DSA?",
        "3. What is the size of int usually in C++?",
        "4. Which symbol ends a C++ statement?",
        "5. Which data structure follows FIFO?"
    };

    string options[5][4] = {
        {"A. Central Processing Unit", "B. Computer Personal Unit",
         "C. Central Program Utility", "D. Control Processing User"},
        {"A. HTML", "B. CSS", "C. C++", "D. SQL"},
        {"A. 1 byte", "B. 2 bytes", "C. 4 bytes", "D. 8 bytes"},
        {"A. :", "B. ;", "C. ,", "D. ."},
        {"A. Stack", "B. Queue", "C. Tree", "D. Graph"}
    };

    char answers[5] = {'A', 'C', 'C', 'B', 'B'};
    char userAnswers[5];

    int score = 0;

    cout << "=== Online Exam System ===\n";
    cout << "Answer the following 5 questions.\n";

    for (int i = 0; i < 5; i++) {
        cout << "\n" << questions[i] << endl;

        for (int j = 0; j < 4; j++) {
            cout << options[i][j] << endl;
        }

        cout << "Your answer (A/B/C/D): ";
        cin >> userAnswers[i];

        // Convert answer to uppercase
        if (userAnswers[i] >= 'a' && userAnswers[i] <= 'z') {
            userAnswers[i] = userAnswers[i] - 'a' + 'A';
        }

        if (userAnswers[i] == answers[i]) {
            cout << "Correct!\n";
            score++;
        }
        else {
            cout << "Wrong! Correct answer: "
                 << answers[i] << endl;
        }
    }

    cout << "\n=== Exam Result ===\n";
    cout << "Total questions: 5\n";
    cout << "Correct answers: " << score << endl;
    cout << "Wrong answers: " << 5 - score << endl;
    cout << "Final score: " << score << "/5\n";
    cout << "Percentage: " << score * 20 << "%\n";

    if (score >= 3) {
        cout << "Result: PASS\n";
    }
    else {
        cout << "Result: FAIL\n";
    }

    return 0;
}
