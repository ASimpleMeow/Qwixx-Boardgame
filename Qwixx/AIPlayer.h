#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Player.h"

class AIPlayer : public Player {
private:
	bool singleMove(std::vector<Die>& dice, const int& value);
	void doubleMove(std::vector<Die>& dice, int& value);

	/* Decision and Movement Functions */
	bool moveRow(const int& value, int rowIndex, std::vector<Die>& dice);
	bool checkRow(const int& value, const int& rowIndex, std::vector<Die>& dice);
	bool checkShortestDistance(int row, const int& value, int minDistance, std::vector<Die>& dice);
	bool finalAttempt(std::vector<Die>& dice, int& value);
	bool completeMove(const int& board, const int& value, std::vector<Die>& dice);

	/* Helful Misc Function */
	void getColourIndex(std::vector<Die>& dice, int& index, bool smallestSize);
public:
	AIPlayer(bool isHuman, int playerNo);
	~AIPlayer();
	virtual void move(std::vector<Die>& dice, int& value, bool& makeTwoMoves); //Overriding Player's move function
};

#endif // !AIPLAYER_H


