#include "GraphAlgos.h"

GraphAlgos::GraphAlgos(Graph graph) : graph(graph)
{
	m_open_set = PriorityQueue();
}

pair<deque<int>, int> GraphAlgos::findPath(int v1, int v2)
{
	reset();
	assert(v1 < graph.getNumVertices());
	assert(v2 < graph.getNumVertices());

	last_vertex = v1;

	// Put origin in closed set
	addToClosedSet(PathEdge(last_vertex, 0, -1));

	PathEdge next_node;
	while (true)
	{
		// Put neighbors in open set
		int cur_edge = m_closed_set.find(last_vertex)->second.first;
		addNeighborsToOpenSet(last_vertex, cur_edge);

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

pair<deque<PathEdge>, int> GraphAlgos::findPrimTree()
{
	reset();
	deque<PathEdge> prim;

	// Choose a node to start
	last_vertex = 0;

	// Put origin in closed set
	addToClosedSet(PathEdge(last_vertex, 0, -1));
	// Put neighbors in open set
	addNeighborsToOpenSet(last_vertex);

	PathEdge next_node;
	while (m_open_set.size())
	{
		// Bring in smallest open set cost
		next_node = m_open_set.useTop();
		
		// If not already in closed set
		if (m_closed_set.find(next_node.getVertex()) == m_closed_set.end())
		{
			addToClosedSet(next_node);
			prim.push_back(next_node);

			// Check if found complete tree
			if (m_closed_set.size() == graph.getNumVertices())
			{
				int total_edge(0);
				for (auto it = m_closed_set.begin(); it != m_closed_set.end(); it++)
				{
					total_edge += it->second.first;
				}
				return pair<deque<PathEdge>, int>(prim, total_edge);
			}
		}
	}
	// Tree does not exist, return -1
	deque<PathEdge> dummy_path;
	dummy_path.emplace_back(PathEdge(-1, -1, -1));
	return pair<deque<PathEdge>, int>(dummy_path, -1);
}

void GraphAlgos::addToClosedSet(PathEdge next_node)
{
	int next_vertex = next_node.getVertex();
	int next_edge_cost = next_node.getCost();
	int next_prev_vertex = next_node.getPrevVertex();

	auto val = pair<int, int>(next_edge_cost, next_prev_vertex);
	m_closed_set.insert(map<int, pair<int, int>>::value_type(next_vertex, val));
	last_vertex = next_vertex;
}

void GraphAlgos::addNeighborsToOpenSet(int vertex, int add_edge_val)
{
	vector<int> nb = graph.getNeighbors(vertex);
	for (auto v : nb)
	{
		if (m_closed_set.find(v) == m_closed_set.end())
		{
			m_open_set.insert(PathEdge(v, add_edge_val + graph.getEdgeValue(vertex, v), last_vertex));
		}
	}
}

void GraphAlgos::reset()
{
	m_closed_set.clear();
	m_open_set.clear();
}