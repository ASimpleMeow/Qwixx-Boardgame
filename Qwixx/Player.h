#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Die.h"

class Player {
protected:
	std::vector<std::vector<std::string>*>* m_rows;			//four rows of the player
	bool m_isHuman;											//is this player human?
	int m_playerNo;											//the players number
	int m_fails;											//how many passes were made
	std::string m_board;									//all row status of the player
	void printRow(const std::vector<std::string>& row);				//print given row
public:
	Player(bool isHuman, int playerNo);
	virtual ~Player();
	virtual bool move(int& board, int& value);
	virtual bool move(const std::vector<Die>& dice, bool& makeTwoMoves);
	int countScore() const;
	const std::vector<std::vector<std::string>*>* const getBoard();
	int& getFails();
	int& getPlayerNo();
	void incrementFails();
	const bool& isHuman();
	const std::string& const printBoard();
};

#endif // !PLAYER_H

