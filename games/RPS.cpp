#include "RPS.h"
#include <iostream>
#include <limits> // for std::numeric_limits
#include <random> // for std::random_device / std::mt19937 / std::uniform_int_distribution<>
#include <algorithm> // for std::find
#include <cctype> // for std::tolower
#include <string_view> //for std::string_view
#include <iomanip> // for std::left and std::setw


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

// Get some initial inputs based on play choice
void initialization(char choice, std::string& p1n, std::string& p2n, int& loops) {
    if (choice == '3') {
        std::cout << "How many rounds would you like the computer to play?\n";
        std::cout << "Number: ";
        std::cin >> loops;
        p1n = "Computer 1";
        p2n = "Computer 2";
    } else {
        std::cout << "player 1 - Please enter your name: ";
        std::getline(std::cin >> std::ws,p1n);
        if (choice == '1') {
            p2n = "The Computer";
        } else if (choice == '2') {
            std::cout << "Player 2 - Please enter your name: ";
            std::getline(std::cin >> std::ws,p2n);
        }
    }
}

void getInputs(char playStyle, std::string p1n, char& p1c, std::string p2n, char& p2c) {
    if (playStyle == '1') {
        p1c = getPlayerInput(p1n);
        p2c = getComputerInput();
    } else if (playStyle == '2') {
        p1c = getPlayerInput(p1n);
        std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
        p2c = getPlayerInput(p2n);
    } else {
        p1c = getComputerInput();
        p2c = getComputerInput();
    }
}

// Asks for and returns the player input
char getPlayerInput(std::string name) {
    char choice {};
    char options[] {'r','p','s'};
    std::cout << name <<"! Make your choice!\n";
    do {
        std::cout << "Enter 'r' for Rock, 'p' for Paper, or 's' for Scissors\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        choice = char(std::tolower(choice));
    } while(!isValid(choice, options, sizeof(options)));

    return choice;
}

char getComputerInput() {
    char options[] {'r','p','s'};
    std::random_device rd; // Use std::random_device to obtain a seed for the random number engine
    std::mt19937 rng(rd()); // Use std::mt19937 as the random number engine (Mersenne Twister)
    std::uniform_int_distribution<int> distribution(0, sizeof(options) - 1); // Uniform distribution over options array

    return options[distribution(rng)];
}

// Input validation: checks if the given character is valid based on the options array
bool isValid(char check, char options[], size_t size) {
    if (std::cin.fail() || std::cin.peek() != '\n' || std::find(options, options + size, check) == options + size) {
        std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
        std::cout << "Invalid input. Please enter a single character from the given options.\n";
        std::cin.clear(); // Reset error flags in std::cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        return false;
    }
    return true;
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
    char choice {};
    if (playStyle == '3') {
        ++currentLoop;
        if (currentLoop == loops) {
            return false;
        }
        return true;
    }
    char options[] {'y','n'};
    std::cout << "Would you like to play again?\n";
    do {
        std::cout << "Enter 'y' for Yes or 'n' for no\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        choice = char(std::tolower(choice));
    } while(!isValid(choice, options, sizeof(options)));
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
    return choice == 'y';
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
    initialization(playChoice, player1Name, player2Name, playLoops);
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
    do {
        getInputs(playChoice, player1Name, player1Choice,player2Name ,player2Choice);
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
