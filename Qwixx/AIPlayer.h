#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Player.h"

class AIPlayer : public Player {
private:
	int checkRed();
	int checkYellow();
	int checkGreen();
	int checkBlue();
	int checkLose();
	void commitMove(std::vector<int>* const row);
public:
	AIPlayer(bool isHuman);
	using Player::move;
	void move();
};

#endif // !AIPLAYER_H


