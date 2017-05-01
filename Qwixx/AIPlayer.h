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
	void commitMove(const std::vector<std::string>& row);
public:
	AIPlayer(bool isHuman, int playerNo);
	~AIPlayer();
	virtual bool move(const std::vector<Die>& dice, bool& makeTwoMoves);
};

#endif // !AIPLAYER_H


