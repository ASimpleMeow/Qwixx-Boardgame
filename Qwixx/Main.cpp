//Qwixx Program

#include <iostream>
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Die.h"
#include "KeepRunning.h"

void displayRules();
void makeChoice(int& choice,const std::string& prompt);
bool makeChoiceYesNo(const std::string& prompt);
void displayMenu();
void printRows(Player& player);
void displayPlayerOptions();
bool endGame();
void rollDice(std::vector<Die>& const dice);
bool makeMove(Player& currentPlayer, std::vector<Die>& dice, bool& makeTwoMoves);
void makeSecondMove(Player& currentPlayer, std::vector<Die>& dice, bool& makeTwoMoves, std::string& prompt);
bool carryOutChoice(int& userChoice, int& value, Player& currentPlayer);

int main() {

	//A clever code that uses a decontructor in order to prevent the
	//console window from closing (even when exceptions occur)
	KeepRunning kr;

	int userChoice = 0;			//User chocie for multiple questions
	Player* currentPlayer;		//The currentplayer Player
	int currentPlayerNo = 0;	//The index for the current player
	std::vector<Die> dice{ Die(), Die(), Die("red"), Die("yellow"),Die("green"),Die("blue") };
	std::vector<Player*> players;

	std::string prompt = "Your choice : ";
	std::cout << "Qwixx Game!\n\n";

	backToMenu:
	displayMenu();
	makeChoice(userChoice, prompt);
	if (userChoice == 2) {
		displayRules();
		goto backToMenu;
	} else if (userChoice == 3) {
		std::cout << "Thank you for playing\n\n";
		return 0;
	}
	prompt = "How many players are playing? : ";
	makeChoice(userChoice, prompt);
	while (userChoice < 2) {
		std::cout << "Must be a valid number of 2 or more players\n";
		prompt = "How many players are playing? : ";
		makeChoice(userChoice, prompt);
	}

	//Making userChoice amount of players
	for (int i = 0; i < userChoice; i++) {
		prompt = "Is the player " + std::to_string(players.size()) + " human? (y/n): ";
		if (makeChoiceYesNo(prompt))
			players.push_back(new HumanPlayer(true, i));
		else
			players.push_back(new AIPlayer(false, i));
	}

	currentPlayer = players.at(currentPlayerNo);

	while (!endGame()) {
		rollDice(dice);
		bool makeTwoMoves = true;

		for (int i = 0; i < players.size(); ++i) {
			while (!makeMove(*currentPlayer, dice, makeTwoMoves)) {}
			currentPlayerNo = ++currentPlayerNo%players.size();
			currentPlayer = players.at(currentPlayerNo);
		}
		currentPlayerNo = ++currentPlayerNo%players.size();
		currentPlayer = players.at(currentPlayerNo);
	}
	return 0;
}

bool makeMove(Player& currentPlayer, std::vector<Die>& dice, bool& makeTwoMoves) {
	int value = dice[0].getCurrentDieValue() + dice[1].getCurrentDieValue();
	int userChoice = 0;
	printRows(currentPlayer);
	std::string prompt = "Select an option from the list : ";
	if (currentPlayer.isHuman()) {
		std::cout << "\nTwo white dice value : " << value << "\n";
		displayPlayerOptions();
		makeChoice(userChoice, prompt);
		if (userChoice != 1 && userChoice != 2) {
			std::cout << "\n\nIncorrect option selected, please try again!\n\n";
			return false;
		} 
		if (!carryOutChoice(userChoice, value, currentPlayer)) {
			std::cout << "\n\nInvalid/Illegal move\n\n";
			return false;
		}
		printRows(currentPlayer);
		makeSecondMove(currentPlayer, dice, makeTwoMoves, prompt);
		printRows(currentPlayer);
		return true;
	}

	currentPlayer.move(dice, makeTwoMoves);
	std::cout << "\n\nThe AI made some dumb move again -_- \n" <<
		"Piece of shit never learns\n\n";
	return true;
}

void makeSecondMove(Player& currentPlayer, std::vector<Die>& dice, bool& makeTwoMoves, std::string& prompt) {
	int userChoice = 0;
	int value = 0;
	while (makeTwoMoves) {
		displayPlayerOptions();
		makeChoice(userChoice, prompt);
		if (userChoice != 1 && userChoice != 2) continue;
		if (userChoice == 2) {
			currentPlayer.incrementFails();
			break;
		}
		prompt = "Select which white die to use (0/1) : ";
		makeChoice(value, prompt);
		if (value != 0 && value != 1) continue;
		prompt = "Select a coloured die : ";
		makeChoice(userChoice, prompt);
		if (userChoice < 2 || userChoice >= dice.size()) continue;
		value = dice[value].getCurrentDieValue() + dice[userChoice].getCurrentDieValue();
		userChoice -= 2;
		makeTwoMoves = !currentPlayer.move(userChoice, value);
	}
}

bool carryOutChoice(int& userChoice, int& value, Player& currentPlayer) {
	if (userChoice == 2) {
		currentPlayer.incrementFails();
		return true;
	}
	int row = 0;
	std::cout << "What row do you want to use : ";
	std::cin >> row;
	if (row < 0 || row > 3) return false;
	return currentPlayer.move(row, value);
}

inline void rollDice(std::vector<Die>& const dice) {
	std::cout << "\n\nRolling the Dice! \n";
	int i = 0;
	for (std::vector<Die>::iterator iter = dice.begin(); iter != dice.end(); ++iter) {
		(*iter).roll();
		std::cout << i << " : " <<(*iter).getColour() << " :\t" << (*iter).getCurrentDieValue()<< "\n";
		++i;
	}
	std::cout << "\n\n";
}

bool endGame() {
	return false;
}

inline void makeChoice(int& choice, const std::string& prompt) {
	std::cout << prompt;
	std::cin >> choice;
}

inline bool makeChoiceYesNo(const std::string& prompt) {
	std::cout << prompt;
	char choice = ' ';
	std::cin >> choice;
	if (choice == 'Y' || choice == 'y') return true;
	return false;
}

inline void printRows(Player& player) {
	std::cout << "\n" << player.getPlayerNo() << ((player.isHuman()) ? " Human " : " AI ") << "Player Rows\n";
	std::cout << player.printBoard() << "\n";
}

inline void displayPlayerOptions() {
	std::cout << "\n\nYour options : \n" <<
		"1) Pick a row for your number\n" <<
		"2) Don't pick a number (pass and add to fails)\n";
}

void displayMenu() {
	std::cout << "\nMenu Screen \n" <<
		"1) Start The Game\n" <<
		"2) Read Instructions/Rules\n" <<
		"3) Exit\n";
}

void displayRules() {
	std::cout << "\n                               HOW TO PLAY\n\n" <<
		"You roll 6 dice, then all players(starting from the rolling player) can \nchoose a number off any\n" <<
		"row that the two white dice show.\n" <<
		"Once chosen, the number on the row is crossed off and any number preceeding \nthat one can no longer\n" <<
		"be selected.\n" <<
		"The rolling player gets to also combine a white die with a coloured die and \ncross of a number from the\n" <<
		"coloured die's colour, naturally following the crossing out rule earlier.\n" <<
		"Then the next player goes again, the game ends under the following conidtions : \n" <<
		"1-Two locks (the end of the row) are locked off, Note: you must have 5 numbers \ncrossed out on the same row\n"
		<< "		to cross out a lock! Following that, no one can use that row and the row coloured die is removed.\n" <<
		"2-Someone accumulates 4 fails (Fails are given when the rolling player doesn't \nmake any move on his/her turn).\n" <<
		"\nGood Luck!\n\n";
}