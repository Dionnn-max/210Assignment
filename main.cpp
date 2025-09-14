#include <iostream>
#include <string>
#include <limits>

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& n, int startScore) : name(n), score(startScore) {}
    const std::string& getName() const { return name; }
    int getScore() const { return score; }
    bool hasWon(int target) const { return score >= target; }
    void addToScore(int amount) { score += amount; }
};

void addMove(Player& who, int step) {
    if (step < 1 || step > 3) {
        std::cout << "Invalid move. Only 1, 2, or 3 allowed.\n";
        return;
    }
    who.addToScore(step);
    std::cout << who.getName() << " score: " << who.getScore() << "\n";
}

void useBonus(int* bonusPtr, Player& who) {
    if (bonusPtr == nullptr) return;
    if (*bonusPtr <= 0) {
        std::cout << "Bonus not available.\n";
        return;
    }
    who.addToScore(*bonusPtr);
    std::cout << who.getName() << " used bonus. Score: " << who.getScore() << "\n";
    *bonusPtr = 0;
}

int compStep() {
    static int callCount = 0;
    int move = (callCount % 2 == 0) ? 1 : 2;
    ++callCount;
    return move;
}

int main() {
    const int TARGET = 20;
    Player you("You", 0);
    Player computer("Computer", 0);
    int bonus = 2;
    bool quit = false;

    while (!quit) {
        std::cout << "\nMenu:\n"
                  << "1) Add 1\n"
                  << "2) Add 2\n"
                  << "3) Add 3\n"
                  << "4) Use one-time bonus (+2)\n"
                  << "5) Quit\n"
                  << "Choose: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 5) {
            quit = true;
            break;
        }

        if (choice >= 1 && choice <= 3) {
            addMove(you, choice);
        } else if (choice == 4) {
            useBonus(&bonus, you);
        } else {
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }

        if (you.hasWon(TARGET)) break;
        addMove(computer, compStep());
        if (you.hasWon(TARGET) && computer.hasWon(TARGET)) break;
        if (computer.hasWon(TARGET)) break;
    }

    std::cout << "\nFinal Scores:\n";
    std::cout << you.getName() << ": " << you.getScore() << "\n";
    std::cout << computer.getName() << ": " << computer.getScore() << "\n";

    if (you.hasWon(TARGET) && computer.hasWon(TARGET)) {
        std::cout << "Result: The game is tie\n";
    } else if (you.hasWon(TARGET)) {
        std::cout << "Result: You win the game!\n";
    } else if (computer.hasWon(TARGET)) {
        std::cout << "Result: Computer wins the game!\n";
    } else {
        std::cout << "Result: Game ended early.\n";
    }

    return 0;
}
