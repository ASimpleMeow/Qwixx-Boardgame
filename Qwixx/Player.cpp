#include "Player.h"
#include <iostream>

Player::Player(bool isHuman, int playerNo) 
:m_isHuman(isHuman), m_playerNo(playerNo)
{}

const std::vector<std::string>& Player::getRed() {
	return this->m_red;
}

const std::vector<std::string>& Player:: getYellow() {
	return this->m_yellow;
}

const std::vector<std::string>& Player::getGreen() {
	return this->m_green;
}

const std::vector<std::string>& Player::getBlue() {
	return this->m_blue;
}

int Player::countScore() {
	return 0;
}

int& Player::getFails() {
	return this->m_fails;
}

int& Player::getPlayerNo() {
	return this->m_playerNo;
}

void Player::incrementFails() {
	++this->m_fails;
}

const bool& const Player::isHuman() {
	return this->m_isHuman;
}

bool Player::move(int& board, int& value) {
	return true;
}

bool Player::move(const std::vector<Die*>& dice, bool& makeTwoMoves) {
	return true;
}

void Player::printRow(const std::vector<std::string>& row) {
	
	for (std::vector<std::string>::const_iterator iter = row.begin(); iter != row.end(); ++iter) {
		this->m_board += (((*iter).size()>1)?"":" ") + *iter + "  ";
	}
}

const std::string& const Player::printBoard() {

	this->m_board = "0 : Red Row:     ";
	printRow(this->getRed());
	this->m_board += "\n1 : Yellow Row:  "; 
	printRow(this->getYellow());
	this->m_board += "\n2 : Green Row:   "; 
	printRow(this->getGreen());
	this->m_board += "\n3 : Blue Row:    ";
	printRow(this->getBlue());
	return this->m_board;
}