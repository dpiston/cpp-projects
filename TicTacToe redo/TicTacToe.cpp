#include "TicTacToe.hpp"
#include <iostream>
#include <limits>  // for std::numeric_limits
#include <cctype>  // for std::toupper
#include <string>  // for std::string
#include <iomanip> // for std::left and std::setw

// intialization of TicTacToe - sets all scores to 0 and calls clear board to create a blank 3x3 gird
TicTacToe::TicTacToe() : xScore(0), oScore(0), draw(0)
{
    clearBoard();
}

// inputs blank spaces in the 3x3 board for a fresh start
void TicTacToe::clearBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// prints a board with a key along the top and bottom for user entry, along with seperators for visual representation between rows and columns
void TicTacToe::printBoard()
{
    std::cout << "\033[2J\033[1;1H";
    for (int i = 0; i < 3; i++)
    {
        std::cout << ' ';
        for (int j = 0; j < 3; j++)
        {
            std::cout << board[i][j];
            if (j != 2)
            {
                std::cout << " ┃ ";
            }
        }
        if (i != 2)
        {
            std::cout << "\n━━━━━━━━━━━\n";
        }
    }
    std::cout << "\n\n";
}

void TicTacToe::printBoardKey()
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << " 1 ┃ 2 ┃ 3 \n";
    std::cout << "━━━━━━━━━━━\n";
    std::cout << " 4 ┃ 5 ┃ 6 \n";
    std::cout << "━━━━━━━━━━━\n";
    std::cout << " 7 ┃ 8 ┃ 9 \n\n";
}

// valdates user input, ensuring it was in fact an int
int TicTacToe::validateInput(const std::string &prompt)
{
    int input{};
    while (true)
    {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail() || input < 0 || input > 9)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
        }
        else
        {
            break;
        }
    }
    return input;
}

// prompt player to enter a move and ensures it is valid
void TicTacToe::getPlayerMove(char symbol)
{
    int position{};
    int row{};
    int col{};

    do
    {
        std::cout << symbol << "'s turn!\n\n";
        position = validateInput("Enter position (1 - 9) or 0 for board key: ");
        row = (position - 1) / 3;
        col = position - row * 3 - 1;
    } while (!isValid(row, col, position));

    board[row][col] = symbol;
}

// validates user choice, re-prompts for entry if play is not legal
bool TicTacToe::isValid(int row, int col, int position)
{
    if (position == 0)
    {
        printBoardKey();
        return false;
    }
    if (board[row][col] != ' ')
    {
        std::cout << "Invalid move. Cell is already occupied.\n\n";
        return false;
    }

    return true;
}

// void TicTacToe::computerMove(char symbol)
// {
//     // TODO, adapt minimax formula for computer play, the goal is to have an unbeatable AI
// }

// reads the board for any game over conditions, weather it be a win or a tie
bool TicTacToe::gameOver()
{
    if (rowCheck() || colCheck() || diagCheck() || isFull())
    {
        return true;
    }

    return false;
}

bool TicTacToe::rowCheck()
{
    for (int i = 0; i < 3; ++i)
    {
        // horizontal check
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            scoreCounter(board[i][0]);
            return true;
        }
    }
    return false;
}

bool TicTacToe::colCheck()
{
    for (int i = 0; i < 3; ++i)
    {
        // horizontal check
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            scoreCounter(board[0][i]);
            return true;
        }
    }
    return false;
}

bool TicTacToe::diagCheck()
{
    if ((board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[2][0] != ' ' && board[2][0] == board[1][1] && board[1][1] == board[0][2]))
    {
        scoreCounter(board[1][1]);
        return true;
    }
    return false;
}

bool TicTacToe::isFull()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                std::cout << "It's a tie!";
                return false;
            }
        }
    }
    return true;
}

void TicTacToe::scoreCounter(char winner)
{
    std::cout << winner << " wins!";
    if (winner == 'X')
    {
        ++xScore;
    }
    else
    {
        ++oScore;
    }
}

bool TicTacToe::playAgain()
{
    char choice{};
    do
    {
        std::cout << "Would you like to play again?\n";
        std::cout << "Enter Y/N: ";
        std::cin >> choice;
        choice = char(std::toupper(choice));
        if ((choice != 'Y' && choice != 'N') || std::cin.peek() != '\n')
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n\n";
        }
        else
        {
            clearBoard();
            break;
        }
    } while (true);

    return choice == 'Y';
}

void TicTacToe::printScore()
{
    std::cout << "Thank you for playing!\n";
    std::cout << "Final score:\n";
    std::cout << std::left;
    std::cout << std::setw(16) << "X wins:" << xScore << '\n';
    std::cout << std::setw(16) << "O wins:" << oScore << '\n';
    std::cout << std::setw(16) << "Draws:" << draw << '\n';
}
