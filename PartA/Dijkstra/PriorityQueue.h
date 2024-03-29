#pragma once
#include <queue>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

class PathEdge
{
public:
	PathEdge() : m_vertex(-1), m_cost(-1), m_prev_vertex(-1) {};
	PathEdge(int vertex, int cost, int prev_vertex) : m_vertex(vertex), m_cost(cost), m_prev_vertex(prev_vertex) {};
	int getCost() { return m_cost; };
	int getVertex() { return m_vertex; };
	int getPrevVertex() { return m_prev_vertex; };
	string get() { return "(" + to_string(m_vertex) + "," + 
					to_string(m_prev_vertex) + "," + to_string(m_cost) + ")"; }

private:
	int m_vertex;
	int m_cost;
	int m_prev_vertex;
};

class Comparator
{
public:
	bool operator() (PathEdge& p1, PathEdge& p2)
	{
		return (p1.getCost() > p2.getCost());
	}
};

class PriorityQueue{
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

