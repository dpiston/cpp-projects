#ifndef TICTACTOE_H
    #define TICTACTOE_H

    #include <string>
    #include <vector>

    class TicTacToe
    {
    public:
        TicTacToe();
        void printBoard();
        void getPlayerMove(char symbol);
        // void computerMove(char symbol);
        bool isGameOver();
        bool playAgain();
        void printScore();

    private:
        char board[3][3];
        int xScore;
        int oScore;
        int draw;
        void clearBoard();
        void printBoardKey();
        template <typename T>
        T validateInput(const std::string& prompt, const std::vector<T> &options);
        bool isValid(int row, int col, int position);
        int evaluate();
        bool isMovesLeft();
    };

#endif
