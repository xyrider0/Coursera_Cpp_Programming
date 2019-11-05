#pragma once
#include <queue>
#include <vector>
#include <string>
#include "Node.h"

using namespace std;

class PathEdge
{
public:
	PathEdge() : m_node(nullptr), m_cost(-1), m_prev_node(nullptr) {}
	PathEdge(Node* node, int cost, Node* prev_node) : m_node(node), m_cost(cost), m_prev_node(prev_node) {};
	~PathEdge() {}
	int getCost() { return m_cost; };
	Node* getNode() { return m_node; };
	Node* getPrevNode() { return m_prev_node; };

private:
	Node* m_node;
	int m_cost;
	Node* m_prev_node;
};

class Comparator
{
public:
	bool operator() (PathEdge& p1, PathEdge& p2)
	{
		return (p1.getCost() > p2.getCost());
	}
};

class PriorityQueue {
public:
	PriorityQueue();
	~PriorityQueue();
	PathEdge useTop();
	void insert(const PathEdge& p1);
	void clear();
	int size();

private:
	priority_queue<PathEdge, vector<PathEdge>, Comparator> m_queue;

	// key = node
	// value = distance
};

