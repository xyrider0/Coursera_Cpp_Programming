#include "Node.h"

Node::Node() : m_owner(COLOR::NONE), m_row(-1), m_col(-1)
{
	m_neighbors = std::vector<Node*>();
}

std::ostream& operator<<(std::ostream& out, const Node& node)
{
	std::string icon;
	switch (node.m_owner)
	{
	case COLOR::NONE:
		icon = ".";
		break;
	case COLOR::WHITE:
		icon = "W";
		break;
	case COLOR::BLACK:
		icon = "B";
		break;
	}
	out << icon;
	return out;
}

std::vector<Node*> Node::getNeighbors()
{
	return m_neighbors;
}

void Node::addNeighbor(std::vector<Node*> nodes)
{
	m_neighbors.insert(m_neighbors.end(), nodes.begin(), nodes.end());
	return;
}

void Node::addNeighbor(Node* node)
{
	m_neighbors.push_back(node);
	return;
}

COLOR Node::getColor()
{
	return m_owner;
}

void Node::setColor(COLOR color)
{
	m_owner = color;
	return;
}

void Node::addRow(int row)
{
	m_row = row;
}

void Node::addCol(int col)
{
	m_col = col;
}