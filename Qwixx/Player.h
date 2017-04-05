#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

class Player {
private:
	std::vector<int> m_red{ 2,3,4,5,6,7,8,9,10,11,12 };
	std::vector<int> m_yellow{ 2,3,4,5,6,7,8,9,10,11,12 };
	std::vector<int> m_green{ 12,11,10,9,8,7,6,5,4,3,2 };
	std::vector<int> m_blue{ 12,11,10,9,8,7,6,5,4,3,2 };
	bool m_human;
	int m_fails;
	std::string m_board;
	void printRow(const std::vector<int>* const row);
public:
	Player(bool isHuman);
	void move();
	int countScore();
	std::vector<int>* const getRed();
	std::vector<int>* const getYellow();
	std::vector<int>* const getGreen();
	std::vector<int>* const getBlue();
	int getFails();
	void incrementFails();
	const bool* const isHuman();
	const std::string* const printBoard();
};

#endif // !PLAYER_H

