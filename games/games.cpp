#include "RPS.h"
#include "hangman.h"
#include "ttt.h"
#include <iostream>

int main()
{
    char game{};
    bool play{true};
    do
    {
        std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
        std::cout << "Welcome to my games!\n";
        std::cout << "1) Rock, Paper, Scissors\n";
        std::cout << "2) Hangman\n";
        std::cout << "3) Tic Tac Toe\n";
        std::cout << "4) Exit\n";
        std::cout << "What would you like to play?\n";
        std::cin >> game;
        switch (game)
        {
        case '1':
            rpsMain();
            break;
        case '2':
            hangmanMain();
            break;
        case '3':
            tttMain();
            break;
        case '4':
            std::cout << "Goodbye!\n";
            play = false;
            break;
        default:
            std::cout << "Invalid option.\n";
            break;
        }
    } while (play);
}
