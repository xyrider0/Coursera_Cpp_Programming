#pragma once
#include <vector>
#include <cassert>
#include "PriorityQueue.h"
#include "Node.h"
#include <map>
#include <deque>

using namespace std;
class GraphAlgos {
public:
	GraphAlgos();
	~GraphAlgos();
	pair<deque<Node*>, int> findPath(Node* v1, std::vector<Node*> v2, COLOR color);
	//pair<deque<PathEdge>, int> findPrimTree();

private:
	void addToClosedSet(PathEdge edge);
	void addNeighborsToOpenSet(Node* node, int add_edge_val = 0);
	void reset();
	Node* m_last_node;

	// Key = Node; Value = Cost, PrevNode
	map<Node*, pair<int, Node*>> m_closed_set;
	PriorityQueue m_open_set;
};

