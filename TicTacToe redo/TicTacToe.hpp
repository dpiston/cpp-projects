#ifndef TICTACTOE_H
    #define TICTACTOE_H

    #include <string>

    class TicTacToe
    {
    public:
        TicTacToe();

        void printBoard();
        void getPlayerMove(char symbol);
        // void computerMove(char symbol);
        bool gameOver();
        bool playAgain();
        void printScore();

    private:
        char board[3][3];
        int xScore;
        int oScore;
        int draw;
        void clearBoard();
        void printBoardKey();
        int validateInput(const std::string& prompt);
        bool isValid(int row, int col, int position);
        void scoreCounter(char winner);
        bool rowCheck();
        bool colCheck();
        bool diagCheck();
        bool isFull();
    };

#endif
