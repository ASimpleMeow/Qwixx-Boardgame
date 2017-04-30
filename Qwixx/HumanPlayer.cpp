#include "HumanPlayer.h"


HumanPlayer::HumanPlayer(bool isHuman, int playerNo) : 
Player(isHuman, playerNo)
{}

bool HumanPlayer::move(int& board, int& value) {
	std::vector<std::string>& row = getRow(board);
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

std::vector<std::string>& HumanPlayer::getRow(const int& rowNum) {
	if (rowNum == 0) return m_red;
	if (rowNum == 1) return m_yellow;
	if (rowNum == 2) return m_green;
	return m_blue;
}

