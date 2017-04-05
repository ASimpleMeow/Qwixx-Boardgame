#ifndef DIE_H
#define DIE_H

#include <string>
#include <algorithm>
#include <random>
#include <ctime>

class Die {
private:
	std::string colour;
	int currentDieValue;
public:
	Die(std::string colour = "white");
	const std::string* const getColour();
	void roll();
	const int* const getCurrentDieValue();
};

#endif // !DIE_H

