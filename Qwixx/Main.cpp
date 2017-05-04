/*
* Program Name :	Qwixx
* Author:			Oleksandr Kononov 20071032
* Subject:			Games Development
* Course:			Entertainment Systems
*
* Notes:			The Main class which will be start of the program.
*					It will contain the common vector of dice used commonly between
*					all the players, and the vector of 2-5 players of Player class.
*/

#include <iostream>		 //std::cout, std::cin
#include <algorithm>	 //std::count
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Die.h"
#include "KeepRunning.h"

void makeChoice(int& choice,const std::string& prompt);
bool makeChoiceYesNo(const std::string& prompt);
void displayRules();
void displayResults(std::vector<Player*>& players);
void printRows(Player& player);
void playerOptions(int& userChoice, const std::string& prompt);
bool endGame(std::vector<Player*>& players);
void rollDice(std::vector<Die>& const dice);
bool makeMove(Player& currentPlayer, std::vector<Die>& dice, bool& makeTwoMoves, int& userChoice, std::string& prompt);
void makeSecondMove(Player& currentPlayer, bool& fail, std::vector<Die>& dice, bool& makeTwoMoves, int& userChocie, std::string& prompt);

int main() {

	//Using a destructor to "pause" the program console window when the program finishes
	//since it happens when destructors are called, slow down of the system would be minimal.
	KeepRunning kr;

	int userChoice = 0;			//User chocie for multiple questions
	Player* pCurrentPlayer;		//The pointer towards current player
	int currentPlayerNo = 0;	//The index for the current player
	std::vector<Die> dice{ Die(), Die(), Die("red"), Die("yellow"),Die("green"),Die("blue") };
	std::vector<Player*> players; //Player on the heap
	std::string prompt = "\nMenu Screen \n1) Start The Game\n2) Read Instructions/Rules\n3) Exit\nYour choice : ";

	std::cout << "Qwixx Game!\n\n";
	while (userChoice != 1) {
		makeChoice(userChoice, prompt);
		if (userChoice == 2) displayRules();
		else if (userChoice == 3) {
			std::cout << "Thank you for playing\n\n";
			return 0;
		}
	}
	prompt = "How many players are playing? : ";
	makeChoice(userChoice, prompt);
	while (userChoice < 2 || userChoice > 5) {	//Limit amount of players to 2-5 as per game rules
		std::cout << "Must be a valid number of 2 or more but 5 and less players\n";
		makeChoice(userChoice, prompt);
	}

	//Taking user chocie as amount of players to make, and ask user if player is human or ai
	for (int i = 0; i < userChoice; i++) {
		prompt = "Is the player " + std::to_string(players.size()) + " human? (y/n): ";
		if (makeChoiceYesNo(prompt)) players.push_back(new HumanPlayer(true, i));
		else players.push_back(new AIPlayer(false, i));
	}

	pCurrentPlayer = players.at(currentPlayerNo);	//point to starting player

	while (!endGame(players)) {		//Loop until endGame conditions are met
		rollDice(dice);
		bool makeTwoMoves = true;	//Since rolling player gets two moves(white-white) and (white-colour)

		for (int i = 0; i < players.size(); ++i) {
			while (!makeMove(*pCurrentPlayer, dice, makeTwoMoves, userChoice, prompt)) {}	//Loop until move complete
			if (pCurrentPlayer->getFails() >= 4) break;					//If player fails four times break
			std::cout << "\n\n\n";
			currentPlayerNo = ++currentPlayerNo%players.size();
			pCurrentPlayer = players.at(currentPlayerNo);
		}
		currentPlayerNo = ++currentPlayerNo%players.size();
		pCurrentPlayer = players.at(currentPlayerNo);
	}
	displayResults(players); //Calculate and display results of the game

	//I tried numerous ways to delete the heap Players in the players vector
	//But it always resulted in exceptions, however, since this is the end of the program
	//memory will be freed up once the program ends.
	return 0;
}

//Handles move making, since I want all input/output to take place in the main class.
bool makeMove(Player& currentPlayer, std::vector<Die>& dice, bool& makeTwoMoves, int& userChoice, std::string& prompt) {
	if (dice.size() <= 4) return true;
	int value = dice.at(0).getCurrentDieValue() + dice.at(1).getCurrentDieValue(); //white-white dice value
	if (currentPlayer.isHuman()) {
		userChoice = 0;
		prompt = "Select an option from the list : ";
		bool fail = false;		//Flag this if the player chooses to pass the turn
		printRows(currentPlayer);
		std::cout << "\nTwo white dice value : " << value << "\n";
		playerOptions(userChoice, prompt);
		switch (userChoice) {
			case 2:
				if (!makeTwoMoves) return true;	//If this player is not the rolling player simply return
				fail = true;
				break;
			case 1:
				prompt = "What row do you want to use (0-3): ";
				makeChoice(userChoice, prompt);
				if (userChoice < 0 || userChoice > 3) return false;

				//Check to make sure you can't lock the row unless you have 5 or more X in that row
				int xCount;	//Counting the occurance of X in the selected row
				xCount = std::count(currentPlayer.getBoard()->at(userChoice)->begin(), currentPlayer.getBoard()->at(userChoice)->end(), "X");
				if (value == std::stoi(currentPlayer.getBoard()->at(userChoice)->back()) && xCount < 5) return false;
				else if (value == std::stoi(currentPlayer.getBoard()->at(userChoice)->back())) currentPlayer.removeDie(dice, userChoice);
				
				if (currentPlayer.move(userChoice, value)) break; //If the move returns a false, it will fall through to default
			default:
				return false;
		}
		printRows(currentPlayer);
		makeSecondMove(currentPlayer, fail, dice, makeTwoMoves, userChoice, prompt);
		return true;
	}
	currentPlayer.move(dice, value, makeTwoMoves);
	printRows(currentPlayer);
	return true;
}

//Second move for the human player white-colour dice combo
void makeSecondMove(Player& currentPlayer, bool& fail, std::vector<Die>& dice, bool& makeTwoMoves, int& userChoice, std::string& prompt) {
	if (dice.size() <= 4) return;
	int value = 0; //Will be the value of white + coloured dice
	userChoice = 0;
	while (makeTwoMoves) {
		std::cout << "\n\nWHITE - COLOUR Combo choice";
		prompt = "Select an option from the list : ";
		playerOptions(userChoice, prompt);
		switch (userChoice) {
			case 2:
				if(fail) currentPlayer.incrementFails(); //Since the original fail was flagged, incremement fails
				makeTwoMoves = false; //Prevent other players from getting two moves
				return;
			case 1:
				break;
			default:
				continue;
		}
		prompt = "Select which white die to use (0/1) : ";
		makeChoice(value, prompt);
		if (value != 0 && value != 1) continue;
		prompt = "Select a coloured die : ";
		makeChoice(userChoice, prompt);
		if (userChoice < 2 || userChoice >= dice.size()) continue;
		value = dice.at(value).getCurrentDieValue() + dice.at(userChoice).getCurrentDieValue();
		userChoice = currentPlayer.determineRowFromDice(dice, userChoice);

		//Check to make sure you can't lock the row unless you have 5 or more X in that row
		int xCount = std::count(currentPlayer.getBoard()->at(userChoice)->begin(), currentPlayer.getBoard()->at(userChoice)->end(), "X");
		if (value == std::stoi(currentPlayer.getBoard()->at(userChoice)->back()) && xCount < 5) continue;
		else if (value == std::stoi(currentPlayer.getBoard()->at(userChoice)->back())) currentPlayer.removeDie(dice, userChoice);
		
		makeTwoMoves = !currentPlayer.move(userChoice, value); //If move successful, turn off makeTwoMoves
		if(!makeTwoMoves) printRows(currentPlayer);
	}
}

//Displays player options during the game
inline void playerOptions(int& userChoice, const std::string& prompt) {
	std::cout << "\n\nYour options : \n" <<
		"1) Pick a row for your number\n" <<
		"2) Pass\n";
	makeChoice(userChoice, prompt);
	if (userChoice != 1 && userChoice != 2) {
		std::cout << "\n\nIncorrect option selected, please try again!\n\n";
		userChoice = -1;
	}
}

//Roll the dice and print out to screen the random values
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

//Condtions for ending the game, 2 locked rows or, 4 or more fails.
bool endGame(std::vector<Player*>& players) {
	int count = 0; //Count of locked rows
	std::vector<std::vector<std::string>*>::const_iterator rowsIter;
	for (std::vector<Player*>::const_iterator playerIter = players.begin(); playerIter != players.end(); ++playerIter) {
		if ((*playerIter)->getFails() >= 4) return true;
		rowsIter = (*playerIter)->getBoard()->begin();
		for (; rowsIter != (*(*playerIter)->getBoard()).end(); ++rowsIter) {
			if ((*rowsIter)->back() == "X") count++;
			if (count >= 2) return true;
		}
		count = 0;
	}
	return false;
}

//Get a choice response from the user via prompt and choice (with references)
inline void makeChoice(int& choice, const std::string& prompt) {
	std::cout << prompt;
	std::cin >> choice;
}

//Get a yes/no response from the user to the prompt
bool makeChoiceYesNo(const std::string& prompt) {
	std::cout << prompt;
	char choice = ' ';
	std::cin >> choice;
	if (choice == 'Y' || choice == 'y') return true;
	return false;
}

//Print out the current players rows and fails
inline void printRows(Player& player) {
	std::cout << "\n" << ((player.isHuman()) ? "Human " : "AI ") << "Player "<< player.getPlayerNo()<<
		"	Fails : "<<player.getFails()<<"\n";
	std::cout << player.printBoard() << "\n";
}

//End game results but counting the X's in a single row and getting the score from the scoring chart
//Since it's quicker than making a function to dynamically calculate the score
void displayResults(std::vector<Player*>& players) {
	std::cout << "\n\nRESULTS\n";
	int score;
	std::vector<unsigned int> scoringChart{ 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78 };
	for (std::vector<Player*>::iterator iter = players.begin(); iter != players.end(); ++iter) {
		score = 0;
		for (int row = 0; row < 4; ++row) {
			//xCount for the currentRow of the current player
			int xCount = std::count((*iter)->getBoard()->at(row)->begin(), (*iter)->getBoard()->at(row)->end(), "X");
			score += (xCount > 0)? scoringChart.at(xCount - 1) : 0;
		}
		score -= (*iter)->getFails() * 10;
		std::cout << ((*iter)->isHuman() ? "Human " : "AI ") << "Player " << (*iter)->getPlayerNo()<<" scored " << score << "\n";
	}
}

//Display the (rough) rules to the game 
void displayRules() {
	std::cout << "\n                               HOW TO PLAY\n\n" <<
		"You roll 6 dice, then all 2-5 players(starting from the rolling player) can \nchoose a number off any\n" <<
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