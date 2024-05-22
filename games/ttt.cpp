#include "ttt.h"
#include <iostream>
#include <random> // for std::random_device, std::mt19937, std::uniform_int_distribution
#include <limits> // for std::numeric_limits
#include <array> // for std::array
#include <tuple> // for std::tuple
#include <map> // for std::map


void screenClear()
{
    std::cout << "\033[2J\033[1;1H";  // ANSI escape sequence for clearing screen
}

// Main menu when launching game
char tttMenu() {
    char choice {};
    screenClear();
    std::cout << "-----------------------\n";
    std::cout << "Welcome to Tic Tac Toe!\n";
    std::cout << "-----------------------\n";
    while (true) {
        std::cout << "Chose play style\n";
        std::cout << "1) Single player\n";
        std::cout << "2) Two players\n";
        std::cout << "3) Computer vs Computer\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        if (choice == '1' || choice == '2' || choice == '3') {
            break;
        } else {
            screenClear();
            std::cout << "Please enter a valid option.\n";
        }
    }
    return choice;
}

void printBoard(char board[3][3]) {
	std::cout << '\n';
	for (int x = 0; x < 3; ++x) {
		std::cout << " ";
		for (int y = 0; y < 3; ++y) {
			std::cout << board[x][y];
			if (y != 2) {
				std::cout << " ┃ ";
			}
		}
		if (x !=2) {
			std::cout << "\n━━━━━━━━━━━\n";
		}
	}
	std::cout << "\n\n";
}

void boardHelp() {
	char helpBoard[3][3] {
		{'7','8','9'},
		{'4','5','6'},
		{'1','2','3'}};
	std::cout << "Board input numbers\n";
	printBoard(helpBoard);
}

bool updateBoard(char bd[3][3], int x, int y, char sym) {
	if (bd[x][y] != ' ') {
		std::cout << "Spot is taken, please pick another\n";
		printBoard(bd);
		return false;
	}
	bd[x][y] = sym;
	return true;
}

bool isValid(char bd[3][3], char ch, char sym) {
	std::map<char, std::tuple<int,int>> boardKey {
		{'7',std::make_tuple(0,0)},{'8',std::make_tuple(0,1)},{'9',std::make_tuple(0,2)},
		{'4',std::make_tuple(1,0)},{'5',std::make_tuple(1,1)},{'6',std::make_tuple(1,2)},
		{'1',std::make_tuple(2,0)},{'2',std::make_tuple(2,1)},{'3',std::make_tuple(2,2)}};
	auto it{boardKey.find(ch)};
	if (ch == 'h') {
		boardHelp();
		std::cout << "Press ENTER to continue...";
		std::cin.clear(); // Reset error flags in std::cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
		std::cin.get();
		screenClear();
		printBoard(bd);
		return false;
	} else if (ch == '0') {
		return true;
	} else if (std::cin.fail() || std::cin.peek() != '\n' || it == boardKey.end()) {
		std::cin.clear(); // Reset error flags in std::cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
		std::cout << "Please enter a valid option\n";
		printBoard(bd);
		return false;
	} 
	std::tuple<int,int> element = it -> second;
	int row {std::get<0>(element)};
	int col {std::get<1>(element)};
	if (updateBoard(bd, row, col, sym)) {
		return true;
	}
	return false;
}

// Check all rows for anything that is one move away from winning
bool middleCheck(char bd[3][3], char sym, char oppSym) {
	// Iterate through each row and column, 0 - 2
	for (int row = 0; row < 3; ++row) {
    	for (int col = 0; col < 3; ++col) {
			// If the currently checked row and column is blank, and the two adjacent columns are taken by the opponent, a symbol is placed to block
        	if (bd[row][col] == ' ' && bd[row][(col + 1) % 3] == oppSym && bd [row][(col + 2) % 3] == oppSym) {
            	bd[row][col] = sym;
				// Returns true if a move was made
            	return true;

			// If the currently checked row and column is blank, and the two adjacent rows are taken by the opponent, a symbol is placed to block
        	} else if (bd[row][col] == ' ' && bd[(row + 1) % 3][col] == oppSym && bd [(row + 2) % 3][col] == oppSym) {
            	bd[row][col] = sym;
				// Returns true if a move was made
            	return true;
			}
    	}
		int j {2 - row};
		if (bd[row][row] == ' ' && bd[(row + 1) % 3][(row + 1) % 3] == oppSym && bd[(row + 2) % 3][(row + 2) % 3] == oppSym) {
			bd[row][row] = sym;
			return true;
		} else if (bd[row][j] == ' ' && bd[(row + 1) % 3][(j + 2) % 3] == oppSym && bd[(row + 2) % 3][(j + 1) % 3] == oppSym) {
			bd[row][j] = sym;
			return true;
		}
	}
	return false;
}

bool cornerCheck(char bd[3][3], char sym) {
	if ((bd[0][0] != ' ' && bd[0][0] != sym) || (bd[0][2] != ' ' && bd[0][2] != sym) || (bd[2][0] != ' ' && bd[2][0] != sym) || (bd[2][2] != ' ' && bd[2][2] != sym)) {
		if (bd[1][1] == ' ') {
			bd[1][1] = sym;
			return true;
		}
	} else {
		if (bd[0][1] != ' ' && bd[0][1] != sym && bd[1][0] != ' ' && bd[1][0] != sym && bd[0][0] == ' ') {
			bd[0][0] = sym;
			return true;
		} else if (bd[0][1] != ' ' && bd[0][1] != sym && bd[1][2] != ' ' && bd[1][2] != sym && bd[0][2] == ' ') {
			bd[0][2] = sym;
			return true;
		} else if (bd[1][0] != ' ' && bd[1][0] != sym && bd[2][1] != ' ' && bd[2][1] != sym && bd[2][0] == ' ') {
			bd[2][0] = sym;
			return true;
		} else if (bd[2][1] != ' ' && bd[2][1] != sym && bd[1][2] != ' ' && bd[1][2] != sym && bd[2][2] == ' ') {
			bd[2][2] = sym;
			return true;
		}
	}
	return false;
}

void pickRandom(char bd[3][3], char sym) {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> distribution(0, 3);
	while (true) {
		int row {distribution(rng)};
		int col {distribution(rng)};
		if (bd[row][col] == ' ') {
			bd[row][col] = sym;
			break;
		}
	}
}

void computerMove(char bd[3][3], char compSym) {
	char opponentSym {(compSym == 'X') ? 'O' : 'X'};
	if (boardEmpty(bd)) {
		bd[2][2] = compSym;
	} else if (middleCheck(bd, compSym, opponentSym)) {
	} else if (cornerCheck(bd, compSym)) {
	} else {
		pickRandom(bd, compSym);
	}
}

bool boardEmpty(char bd[3][3]) {
	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			if (bd[x][y] != ' ') {
				return false;
			}
		}
	}
	return true;
}

bool boardFull(char bd[3][3]) {
	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			if (bd[x][y] == ' ') {
				return false;
			}
		}
	}
	return true;
}

bool checkWinner(char bd[3][3]) {
	if (bd[0][0] != ' ') {
		char sym {bd [0][0]};
		if ((bd[0][1] == sym && bd[0][2] == sym) || (bd[1][0] == sym && bd[2][0] == sym) || (bd[1][1] == sym && bd[2][2] == sym)) {
			std::cout << sym << " wins!\n";
			return true;
		}
	} if (bd[1][1] != ' ') {
		char sym {bd [1][1]};
		if ((bd[1][0] == sym && bd[1][2] == sym) || (bd[0][1] == sym && bd[2][1] == sym)) {
			std::cout << sym << " wins!\n";
			return true;
		}
	} if (bd [2][2] != ' ') {
		char sym {bd[2][2]};
		if ((bd[2][0] == sym && bd[2][1] == sym) || (bd[0][2] == sym && bd[1][2] == sym)) {
			std::cout << sym << " wins!\n";
			return true;
		}
	} if (bd [0][2] != ' ') {
		char sym {bd[0][2]};
		if ((bd[1][1] == sym && bd[2][0] == sym)) {
			std::cout << sym << " wins!\n";
			return true;
		}
	} if (boardFull(bd)) {
		std::cout << "It's a tie!\n";
		return true;
	}
	return false;
}

void tttMain() {	
	char board[3][3] {
		{' ',' ',' '},
		{' ',' ',' '},
		{' ',' ',' '}};
	char play {};
	char symbol {'X'};
	char option {tttMenu()};
	screenClear();
	boardHelp();
	do {
		do {
			if ((option == '1' && symbol == 'X') || option == '2') {
				std::cout << symbol << "'s turn\n";
				std::cout << "Enter a space to play, or \"h\" for spot numbers\n";
				std::cout << "Input: ";
				std::cin >> play;
				screenClear();
			} else {
				play = '0';
				computerMove(board, symbol);
				screenClear();
			}
		} while (!isValid(board, play, symbol));
		symbol = (symbol == 'X') ? 'O' : 'X';
		printBoard(board);
	} while (!checkWinner(board));

	std::cout << "Press ENTER to exit...\n";
    std::cin.clear(); // Reset error flags in std::cin
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::cin.get();
    screenClear();
}
