#include "AIPlayer.h"

//Use Player's constructor
AIPlayer::AIPlayer(bool isHuman, int playerNo) 
: Player(isHuman, playerNo)
{}

//Use Player's destructor
AIPlayer::~AIPlayer() {
	Player::~Player();
}

//Use the move functions makeTwoMoves boolean to sepetate into single move or double move
void AIPlayer::move(std::vector<Die>& dice, int& value, bool& makeTwoMoves) {
	makeTwoMoves ? doubleMove(dice, value) : singleMove(dice, value);
	makeTwoMoves = false;	//Make sure the next player doesn't get two turns
}

//Single move : - check the row if the left most spaces are available
//				- if not, then try to determine the shortest distance between last "X" and this value position
//Otherwise return false to signify decision to fail first move
bool AIPlayer::singleMove(std::vector<Die>& dice, const int& value) {
	for (int i = 0; i < 4; ++i) {
		if (checkRow(value, i, dice)) return true; //Check if rows can place value at early position
		//Try to determine the closest next position of no more than two from the last
		if (checkShortestDistance(i, value, 3, dice)) return true;
	}
	return false;
}


//Double move : - Try doing the single move first
//				- Try using the smallest two dice combo's the largest two dice combo's
//				- If all else fails, try finalAttempt solution
//				- (if failed on single move) incremement fails
void AIPlayer::doubleMove(std::vector<Die>& dice, int& value) {
	bool fail = !singleMove(dice, value);		//Check if a move was not made
	int smallestColourIndex = 2;
	int largestColourIndex = 2;
	int whiteIndex = (dice.at(0).getCurrentDieValue() < dice.at(1).getCurrentDieValue()) ? 0 : 1;

	getColourIndex(dice, smallestColourIndex, true);	//Gets die index for the smallest value
	value = dice.at(whiteIndex).getCurrentDieValue() + dice.at(smallestColourIndex).getCurrentDieValue();
	
	//For rows red and yellow
	if (moveRow(value, determineRowFromDice(dice, smallestColourIndex), dice)) return;

	whiteIndex = (whiteIndex == 0) ? 1 : 0; //Since we have the smallest white right now, switch to the other white die
	getColourIndex(dice, largestColourIndex, true); //Gets die index for the largest value
	value = dice.at(whiteIndex).getCurrentDieValue() + dice.at(largestColourIndex).getCurrentDieValue();
	
	//For rows green and blue
	if (moveRow(value, determineRowFromDice(dice, largestColourIndex), dice)) return;

	if(finalAttempt(dice, value)) return;	//If all else fails try brute force final attempt
	if (fail) incrementFails();				//If failed single move, increment fails
}


/* Decision and Movement Functions */

//Perform the checkRow check and the shortestDistance check for the given row, if both are no good, return false
bool AIPlayer::moveRow(const int& value, int rowIndex, std::vector<Die>& dice) {
	if (checkRow(value, rowIndex, dice)) return true;
	if (checkShortestDistance(rowIndex, value, 3, dice)) return true;
	return false;
}

//Checks if the currentRow can hold the value at the early part of the row
bool AIPlayer::checkRow(const int& value, const int& rowIndex, std::vector<Die>& dice) {
	int numberIndex = (rowIndex < 2) ? (value - 2) : (12 - value); //value's position on the row
	if (4 - ((rowIndex<2)?value:12-value) >= 0) {	//Check if value is within allowed distance from the start
		//Check if the position is not already occupied or unavailable
		if (m_rows->at(rowIndex)->at(numberIndex) != "X" && m_rows->at(rowIndex)->at(numberIndex) != "-") {
			return completeMove(rowIndex, value, dice);
		}
	}
	return false;
}

//Checking the shortest distance between the value's position on the row and last X position
//minDistace is the limit on how largest the shortestDistance can be to be accepted as a good move
bool AIPlayer::checkShortestDistance(int row, const int& value, int minDistance, std::vector<Die>& dice) {
	std::vector<std::string>::reverse_iterator rowIter; //Starting from the back to find last X on the row(s)
	int shortestDistance = 12; //Default is the length of the row
	int positionOfValue = 13; //Position of the value in the row
	std::size_t rowIndex = 0; //The row which we're dealing with

	//If row has not "X"'s, return false
	if (std::count(m_rows->at(row)->begin(), m_rows->at(row)->end(), "X") == 0) return false;
	positionOfValue = 13;
	//Start iterating from the end of the current row
	for (rowIter = m_rows->at(row)->rbegin(); rowIter != m_rows->at(row)->rend(); ++rowIter) {
		if (*rowIter == std::to_string(value)) {
			positionOfValue = std::distance(m_rows->at(row)->rbegin(), rowIter);
			continue;
		} else if (*rowIter == "X") {
			if (positionOfValue == 13) return false; //If the last X is found but not the value position then return false
			int distance = std::distance(m_rows->at(row)->rbegin(), rowIter) - positionOfValue; //Distance between the X position and value position
			if (distance > 0 && distance < shortestDistance) {
				shortestDistance = distance;
				rowIndex = row;
			}
			break; //Since last X is found, start on the next row
		}
	}
	//If the shortestDistance is within the given limit, try to complete the move
	if (shortestDistance <= minDistance)
		if (completeMove(rowIndex, value, dice)) return true;
	return false;
}

//Use the brute force method of trying every combination of white-colour dice until one
//works, or you fail to find a good move, then fail
bool AIPlayer::finalAttempt(std::vector<Die>& dice, int& value) {

	for (std::size_t white = 0; white < 2; ++white) {					//White die
		for (std::size_t colour = 2; colour < dice.size(); ++colour) {	//Colour die
			value = dice.at(white).getCurrentDieValue() + dice.at(colour).getCurrentDieValue();
			for (int i = 0; i < 4; ++i) {									//For every row
				if (checkRow(value, i, dice)) return true;
				if (checkShortestDistance(i, value, 4, dice)) return true;
			}
		}
	}
	return false;
}

//Try to complete the move with the value on the rowIndex
bool AIPlayer::completeMove(const int& rowIndex, const int& value, std::vector<Die>& dice) {
	std::vector<std::string>& row = *m_rows->at(rowIndex);	//Reference the row on the rowIndex

	//If you're placing the ending values of the row, check if you can do it
	//If you can, remove the die from the dice
	if ((rowIndex < 2 && value == 12) || (rowIndex >= 2 && value == 2)) {
		if (std::count(row.begin(), row.end(), "X") < 5) return false;
		else removeDie(dice, rowIndex);
	}

	//Iterating backwards from the value position to add the "-" until "X" is met or rend() is reached
	std::vector<std::string>::reverse_iterator iter;
	iter = (rowIndex < 2) ? row.rend() - (value - 2) : row.rend() - (12 - value);
	for (; iter != row.rend(); ++iter) {
		if (*iter == "X") break;
		*iter = "-";
	}
	row.at((rowIndex<2) ? value - 2 : 12 - value) = "X";
	return true;
}



/* Helpful Misc Functions */

//Determine the smallest or largest colour die and return it's index
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

//Return the row index from the given die index using the colours
int& AIPlayer::determineRowFromDice(std::vector<Die>& dice, int& dieIndex) {
	if (dice.at(dieIndex).getColour().compare("red") == 0)  return (dieIndex = 0);
	if (dice.at(dieIndex).getColour().compare("yellow") == 0)  return (dieIndex = 1);
	if (dice.at(dieIndex).getColour().compare("green") == 0)  return (dieIndex = 2);
	if (dice.at(dieIndex).getColour().compare("blue") == 0)  return (dieIndex = 3);
}

//Determine which colour die to remove and remove it
void AIPlayer::removeDie(std::vector<Die>& dice, const int& rowIndex){
	std::string rowColour = "";
	if (rowIndex == 0) rowColour = "red";
	else if (rowIndex == 1) rowColour = "yellow";
	else if (rowIndex == 2) rowColour = "green";
	else if (rowIndex == 3) rowColour = "blue";

	//Start iterating from begin()+2 to ignore the two white dice
	for (std::vector<Die>::iterator iter = dice.begin() + 2; iter != dice.end(); ++iter) {
		if (iter->getColour().compare(rowColour) == 0) {
			dice.erase(dice.begin() + std::distance(dice.begin(), iter));
			return;
		}
	}
}

