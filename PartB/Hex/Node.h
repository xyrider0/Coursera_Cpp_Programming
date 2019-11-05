/*
	Node Class:
	Represents a valid square in the HexBoard class;
*/

#pragma once

#include <vector>
#include <cstdlib>
#include <iostream>
#include "ColorEnum.h"

class Node {
public:
	Node();
	void addNeighbor(Node* node);
	void addNeighbor(std::vector<Node*> nodes);
	void addRow(int row);
	void addCol(int col);
	std::vector<Node*> getNeighbors();
	COLOR getColor();
	void setColor(COLOR color);
	friend std::ostream& operator<<(std::ostream& out, const Node& node);

private:
	std::vector<Node*> m_neighbors;
	COLOR m_owner;
	int m_row;
	int m_col;
};