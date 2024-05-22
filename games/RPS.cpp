#include "RPS.h"
#include <iostream>
#include <limits>      // for std::numeric_limits
#include <random>      // for std::random_device / std::mt19937 / std::uniform_int_distribution<>
#include <cctype>      // for std::tolower
#include <string>      // for std::string
#include <vector>      // for std:vector
#include <iomanip>     // for std::left and std::setw
#include <algorithm>   // for std::find
#include <string_view> //for std::string_view

void clearScreen()
{
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
}

// Main menu when launching game
char rpsMenu()
{
    char choice{};
    clearScreen();
    std::cout << "-------------------------------\n";
    std::cout << "Welcome to rock paper scissors!\n";
    std::cout << "-------------------------------\n";
    while (true)
    {
        std::cout << "Chose play style\n";
        std::cout << "1) Single player\n";
        std::cout << "2) Two players\n";
        std::cout << "3) Computer vs Computer\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        if (choice == '1' || choice == '2' || choice == '3')
        {
            break;
        }
        else
        {
            clearScreen();
            std::cout << "Please enter a valid option.\n";
        }
    }
    return choice;
}

// Asks for player names
std::string getName(std::string_view player)
{
    std::cout << player << " - Please enter your name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name);

    return name;
}

// Asks for the number of times the computer should play against itself
int getLoops()
{
    int loops{};
    std::cout << "How many rounds would you like the computer to play?\n";
    std::cout << "Number: ";
    std::cin >> loops;

    return loops;
}

void initializePlayers(char playChoice, std::string &player1Name, std::string &player2Name, int &playLoops)
{
    if (playChoice == '3')
    {
        playLoops = getLoops();
        player1Name = "Computer 1";
        player2Name = "Computer 2";
    }
    else
    {
        player1Name = getName("Player 1");
        if (playChoice == '1')
        {
            player2Name = "The Computer";
        }
        else if (playChoice == '2')
        {
            player2Name = getName("Player 2");
        }
    }
}

// Input validation: checks if the given character is valid based on the options array
bool isValid(char check, const std::vector<char> &options)
{
    if (std::cin.fail() || std::cin.peek() != '\n' || std::find(options.begin(), options.end(), check) == options.end())
    {
        clearScreen();
        std::cout << "Invalid input. Please enter a single character from the given options.\n";
        std::cin.clear();                                                   // Reset error flags in std::cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        return false;
    }
    return true;
}

// Asks for and returns the player input
char getPlayerInput(const std::string &name)
{
    char input{};
    std::vector<char> validOptions{'r', 'p', 's'};
    std::cout << name << "! Make your choice!\n";
    do
    {
        std::cout << "Enter 'r' for Rock, 'p' for Paper, or 's' for Scissors\n";
        std::cout << "Choice: ";
        std::cin >> input;
        input = char(std::tolower(input));
    } while (!isValid(input, validOptions));

    return input;
}

// Computer picks a number between 0 and 2, which corrispondes to characters within a vector for play choice
char getComputerInput()
{
    std::vector<char> options{'r', 'p', 's'};
    std::random_device rd;                                                                     // Use std::random_device to obtain a seed for the random number engine
    std::mt19937 rng(rd());                                                                    // Use std::mt19937 as the random number engine (Mersenne Twister)
    std::uniform_int_distribution<long long unsigned int> distribution(0, options.size() - 1); // Uniform distribution over options array

    return options[distribution(rng)];
}

// Compares the passed characters to determine who won
int decideWinner(char play, char p1, std::string_view p1n, char p2, std::string_view p2n)
{
    if ((p1 == 'r' && p2 == 's') || (p1 == 's' && p2 == 'p') || (p1 == 'p' && p2 == 'r'))
    {
        if (play != '3')
        {
            std::cout << translate(p1) << " beats " << translate(p2) << ", " << p1n << " wins!\n\n";
        }
        return 1;
    }
    else if ((p2 == 'r' && p1 == 's') || (p2 == 's' && p1 == 'p') || (p2 == 'p' && p1 == 'r'))
    {
        if (play != '3')
        {
            std::cout << translate(p2) << " beats " << translate(p1) << ", " << p2n << " wins!\n\n";
        }
        return 2;
    }
    else
    {
        if (play != '3')
        {
            std::cout << "It's a tie!\n\n";
        }
        return 3;
    }
}

bool playAgain(char playStyle, int loops, int &currentLoop)
{
    if (playStyle == '3')
    {
        ++currentLoop;
        if (currentLoop == loops)
        {
            return false;
        }
        return true;
    }
    char input{};
    std::vector<char> validOptions{'y', 'n'};
    do
    {
        std::cout << "Enter 'y' for Yes or 'n' for no\n";
        std::cout << "Choice: ";
        std::cin >> input;
        input = char(std::tolower(input));
    } while (!isValid(input, validOptions));
    clearScreen();
    return input == 'y';
}

std::string_view translate(char ch)
{
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

void printScore(std::string_view p1n, int p1s, std::string_view p2n, int p2s, int dr)
{
    clearScreen();
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
    clearScreen();
}

void getChoices(char playChoice, const std::string &player1Name, const std::string &player2Name, char &player1Choice, char &player2Choice)
{
    if (playChoice == '1')
    {
        player1Choice = getPlayerInput(player1Name);
        player2Choice = getComputerInput();
    }
    else if (playChoice == '2')
    {
        player1Choice = getPlayerInput(player1Name);
        clearScreen();
        player2Choice = getPlayerInput(player2Name);
    }
    else
    {
        player1Choice = getComputerInput();
        player2Choice = getComputerInput();
    }
}

void displayChoices(const std::string &player1Name, char player1Choice, const std::string &player2Name, char player2Choice)
{
    clearScreen();
    std::cout << player1Name << " chose: " << translate(player1Choice) << "!\n";
    std::cout << player2Name << " chose: " << translate(player2Choice) << "!\n\n";
}

void updateScores(int result, int &player1Score, int &player2Score, int &draws)
{
    switch (result)
    {
    case 1:
        player1Score++;
        break;
    case 2:
        player2Score++;
        break;
    default:
        draws++;
        break;
    }
}

void rpsMain()
{
    int player1Score{0};
    int player2Score{0};
    int draws{0};
    int playLoops{0};
    int currentLoop{0};
    char player1Choice{};
    char player2Choice{};
    std::string player1Name{};
    std::string player2Name{};
    char playChoice{rpsMenu()};

    clearScreen();
    initializePlayers(playChoice, player1Name, player2Name, playLoops);
    clearScreen();

    do
    {
        getChoices(playChoice, player1Name, player2Name, player1Choice, player2Choice);
        // Save some processing time if only computers are playing since it will be too fast to see anyway
        if (playChoice != '3')
        {
            displayChoices(player1Name, player1Choice, player2Name, player2Choice);
        }
        int result{decideWinner(playChoice, player1Choice, player1Name, player2Choice, player2Name)};
        updateScores(result, player1Score, player2Score, draws);
    } while (playAgain(playChoice, playLoops, currentLoop));
    printScore(player1Name, player1Score, player2Name, player2Score, draws);
}
