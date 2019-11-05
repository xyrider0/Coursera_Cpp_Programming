#pragma once
#include <vector>
#include <cassert>
#include "PriorityQueue.h"
#include "Graph.h"
#include <map>
#include <deque>

using namespace std;
class GraphAlgos {
public:
	GraphAlgos(Graph graph);
	pair<deque<int>, int> findPath(int v1, int v2);
	pair<deque<PathEdge>, int> findPrimTree();

private:
	void addToClosedSet(PathEdge node);
	void addNeighborsToOpenSet(int vertex, int add_edge_val = 0);
	void reset();
	int last_vertex;
	
	// Key = Node; Value = Cost, PrevNode
	map<int, pair<int, int>> m_closed_set;
	PriorityQueue m_open_set;
	Graph graph;
};

