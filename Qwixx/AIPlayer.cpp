#include "AIPlayer.h"


AIPlayer::AIPlayer(bool isHuman, int playerNo) 
: Player(isHuman, playerNo)
{}

AIPlayer::~AIPlayer() {
	Player::~Player();
}

void AIPlayer::move(const std::vector<Die>& dice, int& value, bool& makeTwoMoves) {
	makeTwoMoves ? doubleMove(dice, value) : singleMove(dice, value);
}

void AIPlayer::singleMove(const std::vector<Die>& dice, int& value) {
	if (3 - value >= 0) {	//Check red and yellow rows nearest to the start
		for (int i = 0; i < 2; ++i) {
			if (m_rows->at(i)->at(value - 2) != "X" || m_rows->at(i)->at(value - 2) != "-") {
				completeMove(i, value);
				return;
			}
		}

	} else if (3 - (12 - value) >= 0) {	//Check green and blue rows nearest to the start
		for (int i = 2; i < 4; ++i) {
			if (m_rows->at(i)->at(12 - value) != "X" || m_rows->at(i)->at(12 - value) != "-") {
				completeMove(i, value);
				return;
			}
		}
	} else { //Try to determine the closest next position of no more than two from the last
		std::vector<std::string>::reverse_iterator rowIter;
		int shortestDistance = 12;
		int rowIndex = 0;
		for (std::vector<std::vector<std::string>*>::iterator rowsIter = m_rows->begin(); rowsIter != m_rows->end(); ++rowsIter) {
			if (std::count((*rowsIter)->begin(), (*rowsIter)->end(), "X") == 0) continue;
			for (rowIter = (*rowsIter)->rbegin(); rowIter != (*rowsIter)->rend(); ++rowIter) {
				if (*rowIter == "X") {
					int distance = 12 - std::distance((*rowsIter)->rbegin(), rowIter) + 2;
					if (value - distance > 0 && value - distance < shortestDistance) {
						shortestDistance = distance;
						rowIndex = std::distance(m_rows->begin(), rowsIter);
						break;
					}
				}
			}
		}
		if (shortestDistance <= 2) {
			completeMove(rowIndex, value);
		}else if (m_fails > 3) {
			completeMove(rowIndex, value);
		}else if (shortestDistance > 2 && m_fails < 2) {
			incrementFails();
		} else {
			completeMove(rowIndex, value);
		}
	}
}

void AIPlayer::doubleMove(const std::vector<Die>& dice, int& value) {

}

void AIPlayer::completeMove(int& board, int& value) {
	std::vector<std::string>& row = *m_rows->at(board);
	std::vector<std::string>::reverse_iterator iter;
	iter = (board < 2) ? row.rend() - (value - 2) : row.rend() - (12 - value);
	for (; iter != row.rend(); ++iter) {
		if (*iter == "X") break;
		*iter = "-";
	}
	row[(board<2) ? value - 2 : 12 - value] = "X";
}