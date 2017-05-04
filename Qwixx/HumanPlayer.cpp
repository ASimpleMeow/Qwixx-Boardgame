#include "HumanPlayer.h"

//Use Player's constructor
HumanPlayer::HumanPlayer(bool isHuman, int playerNo) : 
Player(isHuman, playerNo)
{}

//Use Player's destructor
HumanPlayer::~HumanPlayer() {
	Player::~Player();
}

//Move function for human player
bool HumanPlayer::move(int& board, int& value) {
	std::vector<std::string>& row = *(m_rows->at(board)); //Get the reference to the specific row
	
	//If the location is already occupied (X) or it's blocked off (-) you return false
	if (board < 2) {
		if (row.at(value - 2) == "X" || row.at(value - 2) == "-") return false;
	}else {
		if (row.at(12 - value) == "X" || row.at(12 - value) == "-") return false;
	}

	//Iterating backwards from the value position to add the "-" until "X" is met or rend() is reached
	std::vector<std::string>::reverse_iterator iter;
	iter = (board < 2) ? row.rend() - (value - 2) : row.rend() - (12 - value); //Start the iter at value position
	for (; iter != row.rend(); ++iter) {
		if (*iter == "X") break;
		*iter = "-";
	}
	row[(board<2)? value - 2: 12 - value] = "X"; //Change the value position to "X"
	return true;
}

