#include <cctype>
#include <string>
#include <string_view>

#ifndef RPS_H
    #define RPS_H
    char rpsMenu();
    void initialization(char choice, std::string& p1n, std::string& p2n, int& loops);
    void getInputs(char playStyle, std::string p1n, char& p1c, std::string p2n, char& p2c);
    char getPlayerInput(std::string name);
    char getComputerInput();
    bool isValid(char check, char options[], size_t size);
    void decideWinner(char play, char p1, std::string_view p1n, int& p1s, char p2, std::string_view p2n, int& p2s, int& dr);
    bool playAgain(char playStyle, int loops, int& currentLoop);
    void printScore(std::string p1n, int p1s, std::string p2n, int p2s, int dr);
    void rpsMain();
#endif
