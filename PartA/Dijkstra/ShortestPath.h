#pragma once
#include <vector>
#include <cassert>
#include "PriorityQueue.h"
#include "Graph.h"
#include <map>
#include <deque>

using namespace std;
class ShortestPath {
public:
	ShortestPath(Graph graph);
	pair<deque<int>, int> findPath(int v1, int v2);
	int pathSize(int v1, int v2);

private:
	void addToClosedSet(PathNode node);
	void addNeighborsToOpenSet(int vertex);
	int last_vertex;
	
	// Key = Node; Value = Cost, PrevNode
	map<int, pair<int, int>> m_closed_set;
	PriorityQueue m_open_set;
	Graph graph;
};

ShortestPath::ShortestPath(Graph graph) : graph(graph) 
{
	m_open_set = PriorityQueue();
}

pair<deque<int>, int> ShortestPath::findPath(int v1, int v2)
{
	assert(v1 < graph.getNumVertices());
	assert(v2 < graph.getNumVertices());

	last_vertex = v1;

	// Put origin in closed set
	addToClosedSet(PathNode(last_vertex, 0, -1));

	PathNode next_node;
	while (true)
	{
		// Put neighbors in open set
		addNeighborsToOpenSet(last_vertex);

		// Bring in smallest open set cost to closed set
		// In format (vertex, edge)
			// If destination, stop
		
		if (m_open_set.size())
		{
			next_node = m_open_set.useTop();
		}
		else
		{
			// Path does not exist, return -1 shortest_path and Infinite cost
			deque<int> shortest_path;
			shortest_path.emplace_back(-1);
			int shortest_cost = std::numeric_limits<int>::max();
			return pair<deque<int>, int>(shortest_path, shortest_cost);
		}
		if (next_node.getVertex() == v2)
		{
			// Find shortest cost by referencing closed set
			addToClosedSet(next_node);
			int shortest_cost = m_closed_set.find(last_vertex)->second.first;

			// Trace previous nodes recorded to find shortest path
			deque<int> shortest_path;
			int vert = v2;
			
			shortest_path.push_back(vert);
			while (vert != v1)
			{
				int prev_vertex = m_closed_set.find(vert)->second.second;
				shortest_path.push_front(prev_vertex);
				vert = prev_vertex;
			}

			return pair<deque<int>, int>(shortest_path, shortest_cost);
		}
		else if (m_closed_set.find(next_node.getVertex()) == m_closed_set.end())
		{
			// No previous path to this node, add to closed set
			addToClosedSet(next_node);
		}
		else
		{
			// Skip since shortest path already found
		}
	}

	// Put neighbors in open set, updating values if necessary
}

void ShortestPath::addToClosedSet(PathNode next_node)
{
	int next_vertex = next_node.getVertex();
	int next_edge_cost = next_node.getCost();
	int next_prev_vertex = next_node.getPrevVertex();

	auto val = pair<int, int>(next_edge_cost, next_prev_vertex);
	m_closed_set.insert(map<int, pair<int, int>>::value_type(next_vertex, val));
	last_vertex = next_vertex;
}

void ShortestPath::addNeighborsToOpenSet(int vertex)
{
	vector<int> nb = graph.getNeighbors(vertex);
	int cur_edge = m_closed_set.find(vertex)->second.first;
	for (auto v : nb)
	{
		if (m_closed_set.find(v) == m_closed_set.end())
		{
			m_open_set.insert(PathNode(v, cur_edge + graph.getEdgeValue(vertex, v), last_vertex));
		}
	}
}
