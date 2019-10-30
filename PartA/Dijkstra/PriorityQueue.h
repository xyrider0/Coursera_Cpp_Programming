#pragma once
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

class PathNode
{
public:
	PathNode() : m_vertex(-1), m_cost(-1), m_prev_vertex(-1) {};
	PathNode(int vertex, int cost, int prev_vertex) : m_vertex(vertex), m_cost(cost), m_prev_vertex(prev_vertex) {};
	int getCost() { return m_cost; };
	int getVertex() { return m_vertex; };
	int getPrevVertex() { return m_prev_vertex; };

private:
	int m_vertex;
	int m_cost;
	int m_prev_vertex;
};

class Comparator
{
public:
	int operator() (PathNode& p1, PathNode& p2)
	{
		return p1.getCost() < p2.getCost();
	}
};

class PriorityQueue{
public:
	PriorityQueue();
	~PriorityQueue();
	PathNode useTop();
	void insert(PathNode p1);
	int size();

private:
	priority_queue<PathNode, vector<PathNode>, Comparator> m_queue;

	// key = node
	// value = distance
};

