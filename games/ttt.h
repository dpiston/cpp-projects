#ifndef TTT_H
    #define TTT_H
    void screenClear();
    char tttMenu();
    void printBoard(char board[3][3]);
    void boardHelp();
    bool updateBoard(char bd[3][3], int x, int y, char sym);
    bool isValid(char bd[3][3], char ch, char sym);
    bool middleCheck(char bd[3][3], char sym, char oppSym);
    bool cornerCheck(char bd[3][3], char sym);
    void pickRandom(char bd[3][3], char sym);
    void computerMove(char bd[3][3], char sym);
    bool boardEmpty(char bd[3][3]);
    bool boardFull(char bd[3][3]);
    bool checkWinner(char bd[3][3]);
    void tttMain();
#endif
