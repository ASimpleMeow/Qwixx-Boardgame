#ifndef DIE_H
#define DIE_H

#include <string>
#include <algorithm>
#include <random>
#include <ctime>

class Die {
private:
	std::string m_colour;	//Colour of the die
	int m_currentDieValue;	//Current value the die is showing
public:
	Die(std::string colour = "white");
	const std::string& getColour();
	void roll();
	const int& getCurrentDieValue();
};

#endif // !DIE_H

