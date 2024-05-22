#include <iostream>
#include <limits>

class TicTacToe
{
public:
    TicTacToe();

    void printBoard();
    void getPlayerMove(char symbol);
    // void computerMove(char symbol);
    bool gameOver();

private:
    char board[3][3];
    int player1Score;
    int player2Score;
    int draw;
    bool isValid(int row, int col);
};

TicTacToe::TicTacToe() : player1Score(0), player2Score(0), draw(0)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void TicTacToe::printBoard()
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "    1   2   3   \n\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << i + 1 << "   ";
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
            std::cout << "\n   ━━━━━━━━━━━\n";
        }
    }
    std::cout << "\n\n";
}

void TicTacToe::getPlayerMove(char symbol)
{
    int row{};
    int col{};

    do
    {
        std::cout << symbol << "'s turn!\n\n";
        std::cout << "Please enter a row to play on: ";
        std::cin >> row;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cout << "Please enter a column to play on, enter (0) to restart: ";
        std::cin >> col;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!isValid(row, col));

    board[row - 1][col - 1] = symbol;
}

// void TicTacToe::computerMove(char symbol)
// {
//     // TODO, adapt minimax formula for computer play, the goal is to have an unbeatable AI
// }

bool TicTacToe::gameOver()
{
    // horizontal check
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            std::cout << board[i][0] << " wins!";
            return true;
        }
    }

    // vertical check
    for (int i = 0; i < 3; ++i)
    {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[i][i] == board[2][i])
        {
            std::cout << board[0][i] << " wins!";
            return true;
        }
    }

    // diagonal check
    if ((board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[2][0] != ' ' && board[2][0] == board[1][1] && board[1][1] == board[0][2]))
    {
        std::cout << board[1][1] << " wins!";
        return true;
    }

    // full board check
    bool boardFull {true};
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] != ' ')
            {
                boardFull = false;
            }
        }
    }

    if (boardFull)
    {
        std::cout << "It's a tie!";
        return true;
    }

    return false;
}

bool TicTacToe::isValid(int row, int col)
{
    if (col == 0)
    {
        printBoard();
        return false;
    }
    else if (row < 1 || row > 3)
    {
        std::cout << "Row " << row << " is out of limits, please pick again.\n\n";
        return false;
    }
    else if (col < 1 || col > 3)
    {
        std::cout << "Col " << col << " is out of limits, please pick again.\n\n";
        return false;
    }
    else if (board[row - 1][col - 1] != ' ')
    {
        std::cout << "Row " << row << " Column " << col << " is already occupied, please pick again.\n\n";
        return false;
    }

    return true;
}

int main()
{
    TicTacToe game;
    game.printBoard();
    char currentPlay = 'X';
    do
    {
        game.getPlayerMove(currentPlay);
        game.printBoard();
        currentPlay = currentPlay == 'X' ? 'O' : 'X';
    } while (!game.gameOver());

    return 0;
}
