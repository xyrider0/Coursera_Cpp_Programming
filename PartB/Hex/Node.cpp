#include "Node.h"

Node::Node() : owner(COLOR::NONE) {}

std::ostream& operator<<(std::ostream& out, const Node& node)
{
	std::string icon;
	switch (node.owner)
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