/*
	HexBoard Class
	Represents object that holds Hex game information including current state
*/
#pragma once
#include <vector>
#include <cctype>
#include "Node.h"
#include "GraphAlgos.h"

class HexBoard {
public:
	HexBoard(int size = 11);
	~HexBoard();
	void startGame();

private:
// Member Variables
	std::vector<std::vector<Node*>> m_board;
	std::vector<std::vector<COLOR>> m_board_state;
	int m_turns;
	int m_size;
	COLOR m_player;
	COLOR m_computer;
	GraphAlgos m_algo;

// Internal Functions
	void playerSetup();
	void makeMove(COLOR player);
	void printBoard();
	COLOR checkForWinner(bool fullBoard = false);
	pair<int, int> runMC(int numTrials);
};