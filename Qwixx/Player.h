#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <algorithm>
#include "Die.h"

class Player {
protected:
	std::vector<std::vector<std::string>*>* m_rows;			//Four rows of the player
	bool m_isHuman;											//Is this player human?
	int m_playerNo;											//The players number
	int m_fails;											//Passes/fails were made
	std::string m_board;									//All rows information of the player
	void printRow(const std::vector<std::string>& row);		//Print given row
public:
	Player(bool isHuman, int playerNo);						//Constructor
	virtual ~Player();										//Virtual destructor
	virtual bool move(int& board, int& value);				//Virtual move for HumanPlayer
	virtual void move(std::vector<Die>& dice, int& value, bool& makeTwoMoves); //Virtual move for AIPlayer
	const std::vector<std::vector<std::string>*>* const getBoard(); //The the board of rows
	int& getFails();										//Get fails
	int& getPlayerNo();										//Get player number
	void incrementFails();									//Increment fails for this player
	const bool& isHuman();									//Return if the player is human
	const std::string& const printBoard();					//Prepare and return the m_board information
	void removeDie(std::vector<Die>& dice, const int& rowIndex); //Removes specified Die
	int determineRowFromDice(std::vector<Die>& dice, int& dieIndex); //Returns row index for die
};

#endif // !PLAYER_H

