#include <iostream>
#include <vector>

using namespace std;

int calculateScore(const vector<int>& rolls) {
    int score = 0;
    int i = 0;

    for (int frame = 0; frame < 10; ++frame) {
        if (rolls[i] == 10) {
            // Strike
            score += 10 + rolls[i + 1] + rolls[i + 2];
            i += 1;
        } else if (rolls[i] + rolls[i + 1] == 10) {
            // Spare
            score += 10 + rolls[i + 2];
            i += 2;
        } else {
            // Open frame
            score += rolls[i] + rolls[i + 1];
            i += 2;
        }
    }

    return score;
}

int main() {
    vector<int> rolls;
    int roll;

    cout << "Enter the number of pins knocked down in each roll (enter -1 to finish):" << endl;

    while (cin >> roll) {
        if (roll == -1) break;

        if (roll < 0 || roll > 10) {
            cout << "Invalid input! Pins must be between 0 and 10. Try again: ";
            continue;
        }

        rolls.push_back(roll);
    }

    // Validate at least enough rolls to compute a game
    if (rolls.size() < 12) {
        cout << "Not enough rolls provided to calculate a valid score for 10 frames!" << endl;
        return 1;
    }

    int totalScore = calculateScore(rolls);
    cout << "Total Score: " << totalScore << endl;

    return 0;
}
