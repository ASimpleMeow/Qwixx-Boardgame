//Qwixx Program

#include <iostream>
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Die.h"
#include "KeepRunning.h"

void displayRules();
void makeChoice(int* const choice,const std::string* const prompt);
void displayMenu();
void printRows(Player* const player);
void displayPlayerOptions();
bool endGame();
bool carryOutChoice(int* userChoice, Player* currentPlayer);
void rollDice(std::vector<Die*>* const dice);

int main() {

	//A clever code that uses a decontructor in order to prevent the
	//console window from closing (even when exceptions occur)
	KeepRunning kr;



	int userChoice = 0;
	Player* firstPlayer;
	Player* secondPlayer;
	Player* currentPlayer;
	std::vector<Die*> dice{ new Die,new Die,new Die("red"),new Die("yellow"),new Die("green"),new Die("blue") };

	std::string prompt = "Your choice : ";
	std::cout << "Qwixx Game!\n\n";

	backToMenu:
	displayMenu();
	makeChoice(&userChoice, &prompt);
	if (userChoice == 2) {
		displayRules();
		goto backToMenu;
	} else if (userChoice == 3) {
		std::cout << "Thank you for playing\n\n";
		return 0;
	}
	prompt = "Do you want to be player 1 or 2? : ";
	makeChoice(&userChoice, &prompt);
	
	if (userChoice == 1) {
		firstPlayer = new HumanPlayer(true);
		secondPlayer = new AIPlayer(false);
	} else {
		firstPlayer = new AIPlayer(false);
		secondPlayer = new HumanPlayer(true);
	}
	currentPlayer = firstPlayer;

	while (!endGame()) {
		printRows(firstPlayer);
		printRows(secondPlayer);
		rollDice(&dice);
		if (*currentPlayer->isHuman()) {
			displayPlayerOptions();
			prompt = "Select an option from the list : ";
			makeChoice(&userChoice, &prompt);
			if (userChoice > 0 && userChoice < 4) {
				if (carryOutChoice(&userChoice, currentPlayer)) {
					currentPlayer = (currentPlayer == firstPlayer) ? secondPlayer : firstPlayer;
				} else {
					std::cout << "\n\nInvalid/Illegal move\n\n";
				}
			}
			else std::cout << "\n\nIncorrect option selected, please try again!\n\n";

		} else {
			currentPlayer->move();
			std::cout << "\n\nThe AI made some dumb move again -_- \n" <<
				"Piece of shit never learns\n\n";
			currentPlayer = (currentPlayer == firstPlayer) ? secondPlayer : firstPlayer;
		}
	}
	return 0;
}

inline void displayPlayerOptions() {
	std::cout << "\n\nYour options : \n" <<
		"1) Pick a number from the board\n" <<
		"2) Don't pick a number (add to a fail)\n" <<
		"3) Surrender/Giveup\n";
}

inline void makeChoice(int* const choice, const std::string* const prompt) {
	std::cout << *prompt;
	std::cin >> *choice;
}

inline void printRows(Player* const player) {
	std::cout << "\n" << ((player->isHuman()) ? "Human " : "AI ") << "Player Rows\n";
	std::cout << *player->printBoard() << "\n\n";
}

inline void rollDice(std::vector<Die*>* const dice) {
	std::cout << "Rolling the Dice! \n";
	for (std::vector<Die*>::iterator iter = dice->begin(); iter != dice->end(); ++iter) {
		(*iter)->roll();
		std::cout << *(*iter)->getColour() << " : " << *(*iter)->getCurrentDieValue()<< "  ";
	}
}

bool carryOutChoice(int* userChoice, Player* currentPlayer) {
	switch (*userChoice) {
	case 1:
		std::cout << "\n\nGood job, you picked a number, what do you \n" <<
			"want for it? A cookie?\n\n";
		break;
	case 2:
		std::cout << "\n\nOhh wow, you didn't pick a number, what a development!\n" <<
			"Maybe next time you'll just quit the game entirely?\n\n";
		break;
	case 3:
		std::cout << "\n\nSince this feature is not implemented yet, you're gonna \n" <<
			"have to play this game forever!!! WHAHAHAHA!! There is no escape!\n\n";
		break;
	default:
		std::cout << "\n\nTo be honest I have absolutely no idea how you managed to get \n" <<
			"here, I mean really, I made it logically impossible!\n\n";
		return false;
	}
	return true;
}

bool endGame() {
	return false;
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