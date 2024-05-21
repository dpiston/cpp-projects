#include <cctype>
#include <string>
#include <string_view>
#include <vector>

#ifndef RPS_H
    #define RPS_H
    char rpsMenu();
    bool isValid(char check, std::vector<char> options);
    std::string getName(std::string_view player);
    int getLoops();
    char getPlayerInput(std::string name);
    char getComputerInput();
    void decideWinner(char play, char p1, std::string_view p1n, int& p1s, char p2, std::string_view p2n, int& p2s, int& dr);
    bool playAgain(char playStyle, int loops, int& currentLoop);
    std::string_view translate(char ch);
    void printScore(std::string p1n, int p1s, std::string p2n, int p2s, int dr);
    void rpsMain();
#endif
