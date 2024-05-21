// RPS.h
#ifndef RPS_H
    #define RPS_H

    #include <iostream>
    #include <limits>
    #include <random>
    #include <cctype>
    #include <string>
    #include <vector>
    #include <iomanip>
    #include <algorithm>
    #include <string_view>

    // Clears the screen using ANSI escape sequences
    void clearScreen();

    // Displays the main menu and returns the player's choice
    char rpsMenu();

    // Prompts for and returns a player's name
    std::string getName(std::string_view player);

    // Prompts for and returns the number of rounds for computer vs computer mode
    int getLoops();

    // Initializes player names and number of play loops based on the chosen game mode
    void initializePlayers(char playChoice, std::string& player1Name, std::string& player2Name, int& playLoops);

    // Validates player input against a list of valid options
    bool isValid(char check, const std::vector<char>& options);

    // Prompts for and returns a player's move (rock, paper, or scissors)
    char getPlayerInput(const std::string& name);

    // Generates and returns a random move for the computer
    char getComputerInput();

    // Determines the winner of a round and returns 1 if player 1 wins, 2 if player 2 wins, or 3 for a draw
    int decideWinner(char play, char p1, std::string_view p1n, char p2, std::string_view p2n);

    // Checks if the game should continue based on the game mode and current loop count
    bool playAgain(char playStyle, int loops, int& currentLoop);

    // Translates a move character ('r', 'p', 's') into a string representation ("Rock", "Paper", "Scissors")
    std::string_view translate(char ch);

    // Displays the final scores of the game
    void printScore(std::string_view p1n, int p1s, std::string_view p2n, int p2s, int dr);

    // Gets the choices for the current round based on the game mode
    void getChoices(char playChoice, const std::string& player1Name, const std::string& player2Name, char& player1Choice, char& player2Choice);

    // Displays the choices made by the players
    void displayChoices(const std::string& player1Name, char player1Choice, const std::string& player2Name, char player2Choice);

    // Updates the scores based on the result of the current round
    void updateScores(int result, int& player1Score, int& player2Score, int& draws);

    // Main game loop
    void rpsMain();

#endif // RPS_H
