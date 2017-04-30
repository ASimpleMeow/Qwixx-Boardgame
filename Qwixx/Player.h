#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Die.h"

class Player {
protected:
	std::vector<std::string> m_red{ "2","3","4","5","6","7","8","9","10","11","12" };	//red row
	std::vector<std::string> m_yellow{ "2","3","4","5","6","7","8","9","10","11","12" };//yellow row
	std::vector<std::string> m_green{ "12","11","10","9","8","7","6","5","4","3","2" };	//green row
	std::vector<std::string> m_blue{ "12","11","10","9","8","7","6","5","4","3","2" };	//blue row
	bool m_isHuman;											//is this player human?
	int m_playerNo;											//the players number
	int m_fails;											//how many passes were made
	std::string m_board;									//all row status of the player
	void printRow(const std::vector<std::string>& row);				//print given row
public:
	Player(bool isHuman, int playerNo);
	virtual bool move(int& board, int& value);
	virtual bool move(const std::vector<Die*>& dice, bool& makeTwoMoves);
	int countScore();
	const std::vector<std::string>& getRed();
	const std::vector<std::string>& getYellow();
	const std::vector<std::string>& getGreen();
	const std::vector<std::string>& getBlue();
	int& getFails();
	int& getPlayerNo();
	void incrementFails();
	const bool& isHuman();
	const std::string& const printBoard();
};

#endif // !PLAYER_H

