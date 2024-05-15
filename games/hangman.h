#include <string_view>
#include <string>
#include <vector>

#ifndef HANGMAN_H
    #define HANGMAN_H
    void printMan(int x);
    std::string_view getWord();
    bool isValid(char entry);
    char getGuess();
    bool inWord(char ch, std::string_view sv);
    bool wasGuessed(char ch, std::vector<char>& vc);
    void replace(char ch, std::string_view sv, std::string& wd);
    void hangmanMain ();
#endif
