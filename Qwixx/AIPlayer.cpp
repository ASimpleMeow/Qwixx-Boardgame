#include "AIPlayer.h"


AIPlayer::AIPlayer(bool isHuman, int playerNo) 
: Player(isHuman, playerNo)
{}

AIPlayer::~AIPlayer() {
	Player::~Player();
}

bool AIPlayer::move(const std::vector<Die>& dice, bool& makeTwoMoves) {
	return true;
	/*
	int largestPotentialScore = 0;
	int decision = 0;
	int potentialScores[4] = { checkRed(), checkYellow(), checkGreen(), checkBlue() };

	//Determine which row will give the largest scrore
	for (int i = 0; i < 4; ++i) {
		if (potentialScores[i] > largestPotentialScore) {
			largestPotentialScore = potentialScores[i];
			decision = i;
		}
	}

	//Check if the scrore is above a certain threshold
	//ie, if making this move is worth it
	if (potentialScores[decision] > checkLose()) {
		//Do the move
		if (decision == 0) commitMove(this->getRed());
		else if (decision == 1) commitMove(this->getYellow());
		else if (decision == 2) commitMove(this->getGreen());
		else commitMove(this->getBlue());
	}else {
		incrementFails();
	}*/
}

void AIPlayer::commitMove(const std::vector<std::string>& row) {
	//TO-DO
}

int AIPlayer::checkRed() {
	return 0;
}

int AIPlayer::checkYellow() {
	return 0;
}

int AIPlayer::checkGreen() {
	return 0;
}

int AIPlayer::checkBlue() {
	return 0;
}

//Checks that if AI fails to make a move, the game will end with
//the AI losing
int AIPlayer::checkLose() {
	return 0;
}
