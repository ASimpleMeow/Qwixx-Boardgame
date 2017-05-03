#include "AIPlayer.h"
#include <iostream>

AIPlayer::AIPlayer(bool isHuman, int playerNo) 
: Player(isHuman, playerNo)
{}

AIPlayer::~AIPlayer() {
	Player::~Player();
}

void AIPlayer::move(std::vector<Die>& dice, int& value, bool& makeTwoMoves) {
	makeTwoMoves ? doubleMove(dice, value) : singleMove(value);
}

bool AIPlayer::singleMove(const int& value) {
	if (checkRedYellow(value, 0)) return true;
	if (checkRedYellow(value, 1)) return true;
	if (checkGreenBlue(value, 2)) return true;
	if (checkGreenBlue(value, 3)) return true;
	//Try to determine the closest next position of no more than two from the last
	if (checkShortestDistance(0, 4, value, 3)) return true;
	return false;
}

void AIPlayer::doubleMove(std::vector<Die>& dice, int& value) {
	bool fail = !singleMove(value);		//Check if a move was not made
	int whiteIndex = (dice.at(0).getCurrentDieValue() < dice.at(1).getCurrentDieValue()) ? 0 : 1;
	int smallestColourIndex = 2;
	int largestColourIndex = 2;
	
	getColourIndex(dice, smallestColourIndex, true);
	value = dice.at(whiteIndex).getCurrentDieValue() + dice.at(smallestColourIndex).getCurrentDieValue();
	//For rows red and yellow
	if (moveRedYellow(value, smallestColourIndex)) return;

	whiteIndex = (whiteIndex == 0) ? 1 : 0;
	getColourIndex(dice, largestColourIndex, true);
	value = dice.at(whiteIndex).getCurrentDieValue() + dice.at(largestColourIndex).getCurrentDieValue();
	//For rows green and blue
	if (moveGreenBlue(value, largestColourIndex)) return;

	if(finalAttempt(dice, value)) return;
	if (fail) incrementFails();
}

bool AIPlayer::moveRedYellow(const int& value, const int& rowIndex) {
	if (checkRedYellow(value, rowIndex)) return true;
	if (checkShortestDistance(rowIndex - 2, rowIndex - 1, value, 3)) return true;
	return false;
}

bool AIPlayer::moveGreenBlue(const int& value, const int& rowIndex) {
	if (checkGreenBlue(value, rowIndex)) return true;
	if (checkShortestDistance(rowIndex-2, rowIndex-1, value, 3)) return true;
	return false;
}

bool AIPlayer::checkRedYellow(const int& value, const int& rowIndex) {
	if (3 - value >= 0) {	//Check red and yellow rows nearest to the start
		if (m_rows->at(rowIndex)->at(value - 2) != "X" && m_rows->at(rowIndex)->at(value - 2) != "-") {
			std::cout << "checkRedYellow -> Row : " << rowIndex << "   Value : " << value << "\n";
			completeMove(rowIndex, value);
			return true;
		}
	}
	return false;
}

bool AIPlayer::checkGreenBlue(const int& value, const int& rowIndex) {
	if (3 - (12 - value) >= 0) {	//Check green and blue rows nearest to the start
		if (m_rows->at(rowIndex)->at(12 - value) != "X" && m_rows->at(rowIndex)->at(12 - value) != "-") {
			std::cout << "checkGreenBlue -> Row : " << rowIndex << "   Value : " << value << "\n";
			completeMove(rowIndex, value);
			return true;
		}
	}
	return false;
}

bool AIPlayer::checkShortestDistance(int start, int end, const int& value, int minDistance) {
	std::vector<std::string>::reverse_iterator rowIter;
	int shortestDistance = 12;
	std::size_t rowIndex = 0;
	int xCount = 0;
	int largestXCount = 0;
	for (std::size_t row = start; row < end; ++row) {
		xCount = std::count(m_rows->at(row)->begin(), m_rows->at(row)->end(), "X");
		if (xCount == 0) continue;
		for (rowIter = m_rows->at(row)->rbegin(); rowIter != m_rows->at(row)->rend(); ++rowIter) {
			if (*rowIter == "X") {
				int distance = 12 - std::distance(m_rows->at(row)->rbegin(), rowIter) + 2;
				if ((value - distance > 0 && value - distance < shortestDistance) && xCount > largestXCount) {
					shortestDistance = distance;
					rowIndex = row;
					break;
				}
			}
		}
	}
	if (shortestDistance <= minDistance) {
		std::cout << "shortestDistance -> Row : " << rowIndex << "   Value : " << value << "Distance : "<< shortestDistance << "\n";
		completeMove(rowIndex, value);
		return true;
	}
	return false;
}

bool AIPlayer::finalAttempt(std::vector<Die>& dice, int& value) {
	for (std::size_t white = 0; white < 2; ++white) {
		for (std::size_t colour = 2; colour < dice.size(); ++colour) {
			value = dice.at(white).getCurrentDieValue() + dice.at(colour).getCurrentDieValue();
			if (checkShortestDistance(0, 4, value, (m_fails>= 2)? 6:5)) return true;
		}
	}
	return false;
}


bool AIPlayer::completeMove(const int& board, const int& value) {
	std::cout << "Move Made :    Row : " << board<<"   Value : " << value << "\n";
	std::vector<std::string>& row = *m_rows->at(board);
	std::vector<std::string>::reverse_iterator iter;
	iter = (board < 2) ? row.rend() - (value - 2) : row.rend() - (12 - value);
	for (; iter != row.rend(); ++iter) {
		if (*iter == "X") break;
		*iter = "-";
	}
	row.at((board<2) ? value - 2 : 12 - value) = "X";
	return true;
}

void AIPlayer::getColourIndex(std::vector<Die>& dice, int& index, bool smallestSize) {
	if (smallestSize) {
		//Getting the smallest coloured die index
		for (std::vector<Die>::iterator iter = dice.begin() + 2; iter != dice.end() - 2; ++iter) {
			if ((*iter).getCurrentDieValue() < dice.at(index).getCurrentDieValue()) {
				index = std::distance(dice.begin(), iter);
			}
		}
		return;
	}

	//Getting the largest coloured die index
	for (std::vector<Die>::iterator iter = dice.begin() + 4; iter != dice.end(); ++iter) {
		if ((*iter).getCurrentDieValue() > dice.at(index).getCurrentDieValue()) {
			index = std::distance(dice.begin(), iter);
		}
	}
}