#include "TicTacToe.hpp"
#include <iostream>
#include <limits>    // for std::numeric_limits
#include <cctype>    // for std::toupper
#include <string>    // for std::string
#include <iomanip>   // for std::left and std::setw
#include <vector>    // for std::vector
#include <algorithm> // for std::find and std::max
#include <cmath>     // for INFINITY

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

// valdates user input, ensuring it was something in the included options vector
template <typename T>
T TicTacToe::validateInput(const std::string &prompt, const std::vector<T> &options)
{
    T input{};
    while (true)
    {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail() || std::cin.peek() != '\n' || std::find(options.begin(), options.end(), input) == options.end())
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
    std::vector<int> validOptions{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int position{};
    int row{};
    int col{};

    do
    {
        std::cout << symbol << "'s turn!\n\n";
        position = validateInput("Enter position (1 - 9) or 0 for board key: ", validOptions);
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

// implementation of the minimax formula, will try every possible combination of moves from the current board and return the outcomes
float TicTacToe::minimax(int depth, bool isMax)
{
    int score{evaluate()};

    if (score == 10)
    {
        return static_cast<float>(score - depth);
    }
    if (score == -10)
    {
        return static_cast<float>(score + depth);
    }
    if (!isMovesLeft())
    {
        return 0;
    }

    if (isMax)
    {
        float best{-INFINITY};

        for (int x = 0; x < 3; ++x)
        {
            for (int y = 0; y < 3; ++y)
            {
                if (board[x][y] == ' ')
                {
                    board[x][y] = 'X';
                    best = std::max(best, minimax(depth + 1, !isMax));
                    board[x][y] = ' ';
                }
            }
        }

        return best;
    }
    else
    {
        float best{INFINITY};

        for (int x = 0; x < 3; ++x)
        {
            for (int y = 0; y < 3; ++y)
            {
                if (board[x][y] == ' ')
                {
                    board[x][y] = 'O';
                    best = std::min(best, minimax(depth + 1, !isMax));
                    board[x][y] = ' ';
                }
            }
        }

        return best;
    }
}

// finds the best possible move for the comuter
std::vector<int> TicTacToe::findBestMove(bool isMax)
{
    float bestVal{isMax ? -INFINITY : INFINITY};
    std::vector<int> bestMove{-1, -1};

    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            if (board[x][y] == ' ')
            {
                board[x][y] = isMax ? 'X' : 'O';
                float moveVal{minimax(0, !isMax)};
                board[x][y] = ' ';

                if ((isMax && moveVal > bestVal) || (!isMax && moveVal < bestVal))
                {
                    bestMove[0] = x;
                    bestMove[1] = y;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

void TicTacToe::computerMove(bool isMax)
{
    std::vector<int> move{findBestMove(isMax)};
    board[move[0]][move[1]] = isMax ? 'X' : 'O';
}

// check if there are any moves left on the board
bool TicTacToe::isMovesLeft()
{
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            if (board[x][y] == ' ')
            {
                return true;
            }
        }
    }

    return false;
}

// evaluate the board and return a score
int TicTacToe::evaluate()
{
    // row and column check
    for (int i = 0; i < 3; ++i)
    {
        // check rows for victory
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0] == 'X' ? 10 : -10;
        }

        // check columns for victory
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i] == 'X' ? 10 : -10;
        }
    }

    // check diagonals for victory
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[0][0] == 'X' ? 10 : -10;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return board[0][2] == 'X' ? 10 : -10;
    }

    // if no winner, return 0
    return 0;
}

// reads the board for any game over conditions, weather it be a win or a tie
bool TicTacToe::isGameOver()
{
    int result{evaluate()};
    if (result == 10)
    {
        std::cout << "X wins!\n\n";
        ++xScore;
        return true;
    }
    else if (result == -10)
    {
        std::cout << "O wins!\n\n";
        ++oScore;
        return true;
    }
    else if (!isMovesLeft())
    {
        std::cout << "It's a tie!\n\n";
        ++draw;
        return true;
    }

    return false;
}

// asks the player(s) if they would like to play again, then evaluates entry for valid response
bool TicTacToe::playAgain()
{
    std::vector<char> vaildOptions{'Y', 'N', 'y', 'n'};
    char choice{};
    choice = validateInput("Would you like to play again? (Y/N): ", vaildOptions);
    if (choice == 'Y' || choice == 'y')
    {
        clearBoard();
        return true;
    }

    return false;
}

// prints the score board at the end of the game
void TicTacToe::printScore()
{
    std::cout << "Thank you for playing!\n";
    std::cout << "Final score:\n";
    std::cout << std::left;
    std::cout << std::setw(16) << "X wins:" << xScore << '\n';
    std::cout << std::setw(16) << "O wins:" << oScore << '\n';
    std::cout << std::setw(16) << "Draws:" << draw << '\n';
}
