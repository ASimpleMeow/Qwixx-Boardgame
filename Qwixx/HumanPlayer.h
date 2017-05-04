#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

//Class for human players
class HumanPlayer : public Player {
public:
	HumanPlayer(bool isHuman, int playerNo);	//Constructor
	~HumanPlayer();								//Destructor
	virtual bool move(int& board, int& value);	//Human specific move function, overrides Player's move
};

#endif // !HUMANPLAYER_H


