#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime> // Include the <ctime> header for the time function

void displayWord(const std::string& word, const std::vector<bool>& guessed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (guessed[i]) {
            std::cout << word[i] << ' ';
        } else {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

bool isWordGuessed(const std::vector<bool>& guessed) {
    return std::all_of(guessed.begin(), guessed.end(), [](bool b) { return b; });
}

void hangman() {
    std::vector<std::string> words = {"hangman", "apple", "iridecense", "bellpepper"};
    std::string word = words[rand() % words.size()];
    std::vector<bool> guessed(word.length(), false);
    std::vector<char> incorrectGuesses;
    int attemptsLeft = 6;

    while (attemptsLeft > 0 && !isWordGuessed(guessed)) {
        std::cout << "Attempts left: " << attemptsLeft << std::endl;
        displayWord(word, guessed);

        std::cout << "Incorrect guesses: ";
        for (char c : incorrectGuesses) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;

        std::cout << "Enter a letter: ";
        char guess;
        std::cin >> guess;

        if (std::find(incorrectGuesses.begin(), incorrectGuesses.end(), guess) != incorrectGuesses.end()) {
            std::cout << "You already guessed that letter." << std::endl;
            continue;
        }

        bool correctGuess = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess) {
                guessed[i] = true;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            incorrectGuesses.push_back(guess);
            attemptsLeft--;
        }
    }

    if (isWordGuessed(guessed)) {
        std::cout << "Congratulations! You guessed the word: " << word << std::endl;
    } else {
        std::cout << "You ran out of attempts! The word was: " << word << std::endl;
    }
}

int main() {
    srand(time(0));  // Initialize random seed
    hangman();
    return 0;
}
