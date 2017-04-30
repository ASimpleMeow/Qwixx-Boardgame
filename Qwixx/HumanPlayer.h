#ifndef HUMANP_LAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"
class HumanPlayer : public Player {
private:
	std::vector<std::string>& getRow(const int& rowNum);
public:
	HumanPlayer(bool isHuman, int playerNo);
	virtual bool move(int& board, int& value);
};

#endif // !HUMANPLAYER_H


