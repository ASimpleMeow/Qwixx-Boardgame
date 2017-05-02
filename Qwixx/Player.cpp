#include "Player.h"

Player::Player(bool isHuman, int playerNo) 
:m_isHuman(isHuman), m_playerNo(playerNo){
	m_rows = new std::vector<std::vector<std::string>*>();
	m_rows->push_back(new std::vector<std::string>({ "2","3","4","5","6","7","8","9","10","11","12" }));
	m_rows->push_back(new std::vector<std::string>({ "2","3","4","5","6","7","8","9","10","11","12" }));
	m_rows->push_back(new std::vector<std::string>({ "12","11","10","9","8","7","6","5","4","3","2" }));
	m_rows->push_back(new std::vector<std::string>({ "12","11","10","9","8","7","6","5","4","3","2" }));
}

Player::~Player() {
	for (std::vector<std::vector<std::string>*>::iterator iter = m_rows->begin(); iter != m_rows->end(); ++iter) {
		delete (*iter);
	}
	delete m_rows;
	m_rows = 0;
}

const std::vector<std::vector<std::string>*>* const Player::getBoard() {
	return this->m_rows;
}

bool Player::move(int& board, int& value) {
	return false;
}

void Player::move(const std::vector<Die>& dice, int& value, bool& makeTwoMoves) {
}

int Player::countScore() const {
	return 0;
}

int& Player::getFails(){
	return this->m_fails;
}

int& Player::getPlayerNo(){
	return this->m_playerNo;
}

void Player::incrementFails() {
	++this->m_fails;
}

const bool& const Player::isHuman() {
	return this->m_isHuman;
}

void Player::printRow(const std::vector<std::string>& row) {
	
	for (std::vector<std::string>::const_iterator iter = row.begin(); iter != row.end(); ++iter) {
		this->m_board += (((*iter).size()>1)?"":" ") + *iter + "  ";
	}
}

const std::string& const Player::printBoard() {

	this->m_board = "0 : Red Row:     ";
	printRow(*m_rows->at(0));
	this->m_board += "\n1 : Yellow Row:  "; 
	printRow(*m_rows->at(1));
	this->m_board += "\n2 : Green Row:   "; 
	printRow(*m_rows->at(2));
	this->m_board += "\n3 : Blue Row:    ";
	printRow(*m_rows->at(3));
	return this->m_board;
}