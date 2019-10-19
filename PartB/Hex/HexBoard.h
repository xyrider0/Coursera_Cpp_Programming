/*
	HexBoard Class
	Represents object that holds Hex game information including current state
*/
#pragma once
#include <vector>
#include <cctype>
#include "Node.h"
#include "ColorEnum.h"

// rand gives range between 0 and RAND_MAX
// srand(time(NULL)) seeds random number generator to current time


class HexBoard {
public:
	HexBoard(int size = 11);
	~HexBoard();
	void startGame();

private:
// Each node has maximum six connections
// Corner connectivity 2 or three neighbors
// Edge connectivity 4 neighbors
// Internal node 6 neighbors

// Member Variables
	std::vector<std::vector<Node>> m_board;
	int m_size;
	COLOR player;
	COLOR computer;

// Internal Functions
	void playerSetup();
	void makeMove(int player, int row, int column);
	void printBoard();
	int checkForWinner();
};