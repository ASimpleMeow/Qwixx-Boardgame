#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Player.h"

class AIPlayer : public Player {
private:
	bool singleMove(const int& value);
	void doubleMove(std::vector<Die>& dice, int& value);
	bool completeMove(const int& board, const int& value);
	bool checkRedYellow(const int& value, const int& rowIndex);
	bool checkGreenBlue(const int& value, const int& rowIndex);
	bool moveRedYellow(const int& value, const int& rowIndex);
	bool moveGreenBlue(const int& value, const int& rowIndex);
	bool checkShortestDistance(int start, int end, const int& value, int minDistance);
	void getColourIndex(std::vector<Die>& dice, int& index, bool smallestSize);
	bool finalAttempt(std::vector<Die>& dice, int& value);
public:
	AIPlayer(bool isHuman, int playerNo);
	~AIPlayer();
	virtual void move(std::vector<Die>& dice, int& value, bool& makeTwoMoves);
};

#endif // !AIPLAYER_H


