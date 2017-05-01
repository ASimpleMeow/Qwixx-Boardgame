#include "HumanPlayer.h"


HumanPlayer::HumanPlayer(bool isHuman, int playerNo) : 
Player(isHuman, playerNo)
{}

HumanPlayer::~HumanPlayer() {
	Player::~Player();
}

bool HumanPlayer::move(int& board, int& value) {
	std::vector<std::string>& row = *(m_rows->at(board));
	if (row.at(value - 2) == "X" || row.at(value - 2) == "-") {
		return false;
	}
	std::vector<std::string>::reverse_iterator iter;
	iter = (board < 2) ? row.rend() - (value - 2) : row.rend() - (12 - value);
	for (; iter != row.rend(); ++iter) {
		if (*iter == "X") break;
		*iter = "-";
	}
	row[(board<2)? value - 2: 12 - value] = "X";
	return true;
}

