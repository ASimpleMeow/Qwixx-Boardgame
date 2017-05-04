#include "Die.h"

Die::Die(std::string colour) {
	std::transform(colour.begin(), colour.end(), colour.begin(), ::tolower);
	this->m_colour = colour;
	srand(static_cast<unsigned int>(time(0)));	//Seed random
}

const std::string& Die::getColour(){
	return this->m_colour;
}

//Set new value to the die between 1 and 6
void Die::roll() {
	this->m_currentDieValue = (rand() % 6) + 1;
}

const int& Die::getCurrentDieValue() {
	return this->m_currentDieValue;
}
