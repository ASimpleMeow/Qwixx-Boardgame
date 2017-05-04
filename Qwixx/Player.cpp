#include "Player.h"

//Assign the variables and construct the heap rows
Player::Player(bool isHuman, int playerNo) 
:m_isHuman(isHuman), m_playerNo(playerNo){
	m_rows = new std::vector<std::vector<std::string>*>();
	m_rows->push_back(new std::vector<std::string>({ "2","3","4","5","6","7","8","9","10","11","12" }));
	m_rows->push_back(new std::vector<std::string>({ "2","3","4","5","6","7","8","9","10","11","12" }));
	m_rows->push_back(new std::vector<std::string>({ "12","11","10","9","8","7","6","5","4","3","2" }));
	m_rows->push_back(new std::vector<std::string>({ "12","11","10","9","8","7","6","5","4","3","2" }));
}

//Deleting the rows from the heap, and the containing vector for the rows
Player::~Player() {
	for (std::vector<std::vector<std::string>*>::iterator iter = m_rows->begin(); iter != m_rows->end(); ++iter) {
		delete *iter;
	}
	delete m_rows;
	m_rows = 0; //Prevent dangling pointers
}

const std::vector<std::vector<std::string>*>* const Player::getBoard() {
	return this->m_rows;
}

//Since I will be using polymorphism with Player class, I can't have the whole class be fully abstract
//So I leave these move functions here
bool Player::move(int& board, int& value) { return false; }
void Player::move(std::vector<Die>& dice, int& value, bool& makeTwoMoves) {}

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

//Format the rows and put it into the row string
void Player::printRow(const std::vector<std::string>& row) {
	for (std::vector<std::string>::const_iterator iter = row.begin(); iter != row.end(); ++iter) {
		this->m_board += (((*iter).size()>1)?"":" ") + *iter + "  ";
	}
}

//For every row, prepare the m_board string for it and return it's reference
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

//Finds and removes the die for the given row index (colour)
void Player::removeDie(std::vector<Die>& dice, const int& rowIndex) {
	std::string rowColour = "";
	if (rowIndex == 0) rowColour = "red";
	else if (rowIndex == 1) rowColour = "yellow";
	else if (rowIndex == 2) rowColour = "green";
	else if (rowIndex == 3) rowColour = "blue";

	for (std::vector<Die>::iterator iter = dice.begin() + 2; iter != dice.end(); ++iter) {
		if (iter->getColour().compare(rowColour) == 0) {
			dice.erase(dice.begin() + std::distance(dice.begin(), iter));
			return;
		}
	}
}

//Determines which row is for which coloured die
int Player::determineRowFromDice(std::vector<Die>& dice, int& dieIndex) {
	if (dice.at(dieIndex).getColour().compare("red") == 0)  return 0;
	if (dice.at(dieIndex).getColour().compare("yellow") == 0)  return 1;
	if (dice.at(dieIndex).getColour().compare("green") == 0)  return 2;
	if (dice.at(dieIndex).getColour().compare("blue") == 0)  return 3;
}