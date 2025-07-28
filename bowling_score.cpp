#include <iostream>
#include <vector>

using namespace std;

class BowlingGame {
private:
    vector<int> rolls;

public:
    void roll(int pins) {
        rolls.push_back(pins);
    }

    int score() {
        int result = 0;
        int rollIndex = 0;

        for (int frame = 0; frame < 10; ++frame) {
            if (rolls[rollIndex] == 10) { // Strike
                result += 10 + rolls[rollIndex + 1] + rolls[rollIndex + 2];
                rollIndex += 1;
            } else if (rolls[rollIndex] + rolls[rollIndex + 1] == 10) { // Spare
                result += 10 + rolls[rollIndex + 2];
                rollIndex += 2;
            } else {
                result += rolls[rollIndex] + rolls[rollIndex + 1];
                rollIndex += 2;
            }
        }

        return result;
    }

    int getRollSize() {
        return rolls.size();
    }

    int getRoll(int index) {
        return rolls[index];
    }

    void reset() {
        rolls.clear();
    }
};

int getValidatedRoll(int maxPins, const string& prompt) {
    int pins;
    while (true) {
        cout << prompt;
        cin >> pins;

        if (cin.fail() || pins < 0 || pins > maxPins) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number between 0 and " << maxPins << "." << endl;
        } else {
            return pins;
        }
    }
}

int main() {
    BowlingGame game;

    for (int frame = 1; frame <= 10; ++frame) {
        cout << "\n--- Frame " << frame << " ---" << endl;

        if (frame < 10) {
            int roll1 = getValidatedRoll(10, "Roll 1: ");
            game.roll(roll1);

            if (roll1 == 10) {
                cout << "Strike!" << endl;
                continue;
            }

            int roll2;
            while (true) {
                roll2 = getValidatedRoll(10, "Roll 2: ");
                if (roll1 + roll2 > 10) {
                    cout << "Total pins in a frame cannot exceed 10. Enter again." << endl;
                } else {
                    break;
                }
            }
            game.roll(roll2);
        } else { // Frame 10
            int roll1 = getValidatedRoll(10, "Roll 1: ");
            game.roll(roll1);

            int roll2 = getValidatedRoll((roll1 == 10) ? 10 : (10 - roll1), "Roll 2: ");
            game.roll(roll2);

            if (roll1 == 10 || roll1 + roll2 == 10) {
                int roll3 = getValidatedRoll(10, "Roll 3: ");
                game.roll(roll3);
            }
        }
    }

    cout << "\n=== Final Score: " << game.score() << " ===" << endl;

    return 0;
}
