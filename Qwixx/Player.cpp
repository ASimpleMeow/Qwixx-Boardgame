#include "Player.h"
#include <iostream>

Player::Player(bool isHuman) {
	this->m_human = isHuman;
}

void Player::move() {

}

std::vector<int>* const Player::getRed() {
	return &(this->m_red);
}

std::vector<int>* const Player:: getYellow() {
	return &(this->m_yellow);
}

std::vector<int>* const Player::getGreen() {
	return &(this->m_green);
}

std::vector<int>* const Player::getBlue() {
	return &(this->m_blue);
}

int Player::countScore() {
	return 0;
}

int Player::getFails() {
	return this->m_fails;
}

void Player::incrementFails() {
	++this->m_fails;
}

const bool* const Player::isHuman() {
	return &(this->m_human);
}

void Player::printRow(const std::vector<int>* const row) {
	
	for (std::vector<int>::const_iterator iter = row->begin(); iter != row->end(); ++iter) {
		this->m_board += std::to_string(*iter) + " ";
	}
}

const std::string* const Player::printBoard() {

	this->m_board = "Red Row:     ";
	printRow(this->getRed());
	this->m_board += "\nYellow Row:  "; 
	printRow(this->getYellow());
	this->m_board += "\nGreen Row:   "; 
	printRow(this->getGreen());
	this->m_board += "\nBlue Row:    "; 
	printRow(this->getBlue());
	return &(this->m_board);
}