#include "TicTacToe.h"

int main()
{
    TicTacToe game;
    char currentPlay = 'X';
    do
    {
        game.printBoard();
        do
        {
            game.getPlayerMove(currentPlay);
            game.printBoard();
            currentPlay = currentPlay == 'X' ? 'O' : 'X';
        } while (!game.gameOver());
    } while (game.playAgain()); 

    game.printScore();
    
    return 0;
}
