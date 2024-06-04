#include "TicTacToe.hpp"
#include <iostream>
#include <limits>    // for std::numeric_limits
#include <algorithm> // for std::find
#include <cctype>    // for std::toupper

int menu()
{
    int input{};
    std::vector<int> options{1, 2, 3};
    std::cout << "\033[2J\033[1;1H";
    std::cout << "-----------------------\n";
    std::cout << "Welcome to Tic Tac Toe!\n";
    std::cout << "-----------------------\n";
    while (true)
    {
        std::cout << "Chose play style\n";
        std::cout << "1) Single player\n";
        std::cout << "2) Two players\n";
        std::cout << "3) Computer vs Computer\n";
        std::cout << "Enter choice: ";
        std::cin >> input;
        if (std::cin.fail() || std::cin.peek() != '\n' || std::find(options.begin(), options.end(), input) == options.end())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Please enter a valid option.\n\n";
        }
        else
        {
            break;
        }
    }
    return input;
}

int main()
{
    TicTacToe game;
    char currentPlay{};
    int playOption{menu()};
    if (playOption == 1)
    {
        while (true)
        {
            std::vector<char> options{'X', 'x', 'O', 'o'};
            std::cout << "Would you like be 'X' or 'O': ";
            std::cin >> currentPlay;
            if (std::cin.fail() || std::cin.peek() != '\n' || std::find(options.begin(), options.end(), currentPlay) == options.end())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[2J\033[1;1H";
                std::cout << "Please enter a valid option.\n\n";
            }
            currentPlay = static_cast<char>(std::toupper(currentPlay));
            break;
        }
    }

    do
    {
        char currentPlay{'X'};
        game.printBoard();
        do
        {
            if (playOption == 1)
            {
                if (currentPlay == 'X')
                {
                    game.getPlayerMove(currentPlay);
                    game.computerMove(false);
                }
                else
                {
                    game.computerMove(true);
                    game.printBoard();
                    game.getPlayerMove(currentPlay);
                }
            }
            if (playOption == 2)
            {
                game.getPlayerMove(currentPlay);
                currentPlay = currentPlay == 'X' ? 'O' : 'X';
            }
            if (playOption == 3)
            {
                game.computerMove(true);
                game.computerMove(false);
            }
            game.printBoard();
        } while (!game.isGameOver());
    } while (game.playAgain());

    game.printScore();

    return 0;
}
