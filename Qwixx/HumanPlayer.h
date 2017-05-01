#ifndef HUMANP_LAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"
class HumanPlayer : public Player {
public:
	HumanPlayer(bool isHuman, int playerNo);
	~HumanPlayer();
	virtual bool move(int& board, int& value);
};

#endif // !HUMANPLAYER_H


