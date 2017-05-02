#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Player.h"

class AIPlayer : public Player {
private:
	void singleMove(const std::vector<Die>& dice, int& value);
	void doubleMove(const std::vector<Die>& dice, int& value);
	void completeMove(int& board, int& value);
public:
	AIPlayer(bool isHuman, int playerNo);
	~AIPlayer();
	virtual void move(const std::vector<Die>& dice, int& value, bool& makeTwoMoves);
};

#endif // !AIPLAYER_H


