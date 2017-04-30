#ifndef DIE_H
#define DIE_H

#include <string>
#include <algorithm>
#include <random>
#include <ctime>

class Die {
private:
	std::string m_colour;
	int m_currentDieValue;
public:
	Die(std::string colour = "white");
	const std::string& getColour();
	void roll();
	const int& getCurrentDieValue();
};

#endif // !DIE_H

