#ifndef HUMANP_LAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"
class HumanPlayer : public Player {
private:
	std::string name;
public:
	HumanPlayer(bool isHuman, std::string name = "Default Player");
	using Player::move;
	void move();
};

#endif // !HUMANPLAYER_H


