#include "RPS.h"
#include <iostream>
#include <limits> // for std::numeric_limits
#include <random> // for std::random_device / std::mt19937 / std::uniform_int_distribution<>
#include <cctype> // for std::tolower
#include <string> // for std::string
#include <vector> // for std:vector
#include <iomanip> // for std::left and std::setw
#include <algorithm> // for std::find
#include <string_view> //for std::string_view


// Main menu when launching game
char rpsMenu() {
    char choice {};
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
    std::cout << "-------------------------------\n";
    std::cout << "Welcome to rock paper scissors!\n";
    std::cout << "-------------------------------\n";
    while (true) {
        std::cout << "Chose play style\n";
        std::cout << "1) Single player\n";
        std::cout << "2) Two players\n";
        std::cout << "3) Computer vs Computer\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        if (choice == '1' || choice == '2' || choice == '3') {
            break;
        } else {
            std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
            std::cout << "Please enter a valid option.\n";
        }
    }
    return choice;
}

// Input validation: checks if the given character is valid based on the options array
bool isValid(char check, std::vector<char> options) {
    if (std::cin.fail() || std::cin.peek() != '\n' || std::find(options.begin(), options.end(), check) == options.end()) {
        std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
        std::cout << "Invalid input. Please enter a single character from the given options.\n";
        std::cin.clear(); // Reset error flags in std::cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        return false;
    }
    return true;
}

std::string getName(std::string_view player) {
    std::cout << player << " - Please enter your name: ";
    std::string name{};
    std::getline(std::cin >> std::ws,name);

    return name;
}

int getLoops() {
    int loops {};
    std::cout << "How many rounds would you like the computer to play?\n";
    std::cout << "Number: ";
    std::cin >> loops;

    return loops;
}

// Asks for and returns the player input
char getPlayerInput(std::string name) {
    char input {};
    std::vector<char> validOptions {'r','p','s'};
    std::cout << name <<"! Make your choice!\n";
    do {
        std::cout << "Enter 'r' for Rock, 'p' for Paper, or 's' for Scissors\n";
        std::cout << "Choice: ";
        std::cin >> input;
        input = char(std::tolower(input));
    } while(!isValid(input, validOptions));

    return input;
}

char getComputerInput() {
    std::vector<char> options {'r','p','s'};
    std::random_device rd; // Use std::random_device to obtain a seed for the random number engine
    std::mt19937 rng(rd()); // Use std::mt19937 as the random number engine (Mersenne Twister)
    std::uniform_int_distribution<long long unsigned int> distribution(0, options.size() - 1); // Uniform distribution over options array

    return options[distribution(rng)];
}

// Compares the passed characters to determine who won
void decideWinner(char play, char p1, std::string_view p1n, int& p1s, char p2, std::string_view p2n, int& p2s, int& dr) {
    if ((p1 == 'r' && p2 == 's') || (p1 == 's' && p2 == 'p') || (p1 == 'p' && p2 == 'r')) {
        if (play != '3') {
            std::cout << translate(p1) << " beats " << translate(p2) << ", " << p1n << " wins!\n\n";
        }
        ++p1s;
    } else if ((p2 == 'r' && p1 == 's') || (p2 == 's' && p1 == 'p') || (p2 == 'p' && p1 == 'r')) {
        if (play != '3') {
            std::cout << translate(p2) << " beats " << translate (p1) << ", " << p2n << " wins!\n\n";
        }
        ++p2s;
    } else {
        if (play != '3') {
            std::cout << "It's a tie!\n\n";
        }
        ++dr;
    }
}

bool playAgain(char playStyle, int loops, int& currentLoop) {
    if (playStyle == '3') {
        ++currentLoop;
        if (currentLoop == loops) {
            return false;
        }
        return true;
    }
    char input {};
    std::vector<char> validOptions {'y','n'};
    do {
        std::cout << "Enter 'y' for Yes or 'n' for no\n";
        std::cout << "Choice: ";
        std::cin >> input;
        input = char(std::tolower(input));
    } while(!isValid(input, validOptions));
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
    return input == 'y';
}

std::string_view translate(char ch) {
    switch (ch)
        {
        case 'r':
            return "Rock";
        case 'p':
            return "Paper";
        case 's':
            return "Scissors";
        default:
            return "Unknown";
        }
}

void printScore(std::string p1n, int p1s, std::string p2n, int p2s, int dr) {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
    std::cout << "Thank you for playing!\n";
    std::cout << "Final score:\n";
    std::cout << std::left;
    std::cout << std::setw(16) << p1n << ":" << p1s << '\n';
    std::cout << std::setw(16) << p2n << ":" << p2s << '\n';
    std::cout << std::setw(16) << "Draws" << ':' << dr << '\n';
    std::cout << "Press ENTER to exit...\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
}

void rpsMain() {
    int player1Score {0};
    char player1Choice {};
    std::string player1Name {};
    int player2Score {0};
    char player2Choice {};
    std::string player2Name {};
    int draws {0};
    char playChoice {rpsMenu()};
    int playLoops {};
    int currentLoop {0};
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
    if (playChoice == '3') {
        playLoops = getLoops();
        player1Name = "Computer 1";
        player2Name = "Computer 2";
    } else {
        player1Name = getName("Player 1");
        if (playChoice == '1') {
            player2Name = "The Computer";
        } else if (playChoice == '2') {
            player2Name = getName("Player 2");
        }
    }
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
    do {
        if (playChoice == '1') {
            player1Choice = getPlayerInput(player1Name);
            player2Choice = getComputerInput();
        } else if (playChoice == '2') {
            player1Choice = getPlayerInput(player1Name);
            std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
            player2Choice = getPlayerInput(player2Name);
        } else {
            player1Choice = getComputerInput();
            player2Choice = getComputerInput();
        }
        // Save some processing time if only computers are playing since it will be too fast to see anyway
        if (playChoice != '3') {
            std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
            // Print player scores
            std::cout << player1Name << " chose: " << translate(player1Choice) << "!\n";
            std::cout << player2Name << " chose: " << translate(player2Choice) << "!\n\n";
        }
        decideWinner(playChoice, player1Choice, player1Name, player1Score, player2Choice, player2Name, player2Score, draws);
    } while (playAgain(playChoice, playLoops, currentLoop));
    printScore(player1Name, player1Score, player2Name, player2Score, draws);
}
