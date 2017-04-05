#include "Die.h"



Die::Die(std::string colour) {
	std::transform(colour.begin(), colour.end(), colour.begin(), ::tolower);
	this->colour = colour;
	srand(static_cast<unsigned int>(time(0)));
}

const std::string* const Die::getColour(){
	return &(this->colour);
}

void Die::roll() {
	this->currentDieValue = (rand() % 6) + 1;
}

const int* const Die::getCurrentDieValue() {
	return &(this->currentDieValue);
}
