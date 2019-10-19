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
	std::vector<Node> getNeighbors();
	friend std::ostream& operator<<(std::ostream& out, const Node& node);

private:
	std::vector<Node> neighbors;
	COLOR owner;
};