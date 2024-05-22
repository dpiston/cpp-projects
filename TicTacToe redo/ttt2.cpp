#include <iostream>

class TicTacToe
{
    public:
        TicTacToe();
        void printBoard();

    private:
        char board[3][3];
};

TicTacToe::TicTacToe()
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
    for (int i = 0; i < 3; i++)
    {
        std::cout << ' ';
        for (int j = 0; j < 3; j++)
        {
            std::cout << board[i][j];
            if (j != 2) {
				std::cout << " ┃ ";
			}
        }
        if (i != 2) {
			std::cout << "\n━━━━━━━━━━━\n";
		}
    }
}

int main()
{
    TicTacToe game;
    game.printBoard();

    return 0;
}
