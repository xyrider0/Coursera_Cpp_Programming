#include "GraphAlgos.h"

GraphAlgos::GraphAlgos()
{
	m_open_set = PriorityQueue();
	dummy_node = new Node();
}

GraphAlgos::~GraphAlgos()
{
}

// Find path between two nodes with color
pair<deque<Node*>, int> GraphAlgos::findPath(Node* v1, std::vector<Node*> v2, COLOR color)
{
	reset();

	last_node = v1;

	// Put origin in closed set
	addToClosedSet(PathEdge(last_node, 0, dummy_node));

	PathEdge next_edge;
	while (true)
	{
		// Put neighbors in open set
		int cur_edge = m_closed_set.find(last_node)->second.first;
		addNeighborsToOpenSet(last_node, cur_edge);


		// If destination, or first node color is not correct, exit
		if (!m_open_set.size() || last_node->getColor() != color)
		{
			// Path does not exist, return -1 shortest_path and Infinite cost
			deque<Node*> shortest_path;
			shortest_path.emplace_back(dummy_node);
			int shortest_cost = std::numeric_limits<int>::max();
			return pair<deque<Node*>, int>(shortest_path, shortest_cost);
		}
		else
		{
			// Bring in smallest open set cost to closed set
			// In format (node, edge)
			next_edge = m_open_set.useTop();
		}
		if (std::find(v2.begin(), v2.end(), next_edge.getNode()) != v2.end())
		{
			// Find shortest cost by referencing closed set
			addToClosedSet(next_edge);
			int shortest_cost = m_closed_set.find(last_node)->second.first;

			// Trace previous nodes recorded to find shortest path
			deque<Node*> shortest_path;
			Node* node = last_node;

			shortest_path.push_back(node);
			while (node != v1)
			{
				Node* prev_node = m_closed_set.find(node)->second.second;
				shortest_path.push_front(prev_node);
				node = prev_node;
			}

			return pair<deque<Node*>, int>(shortest_path, shortest_cost);
		}
		else if (m_closed_set.find(next_edge.getNode()) == m_closed_set.end())
		{
			// No previous path to this node, add to closed set
			addToClosedSet(next_edge);
		}
		else
		{
			// Skip since shortest path already found
		}
	}

	// Put neighbors in open set, updating values if necessary
}

//pair<deque<PathEdge>, int> GraphAlgos::findPrimTree()
//{
//	reset();
//	deque<PathEdge> prim;
//
//	// Choose a node to start
//	last_node = 0;
//
//	// Put origin in closed set
//	addToClosedSet(PathEdge(last_node, 0, -1));
//	// Put neighbors in open set
//	addNeighborsToOpenSet(last_node);
//
//	PathEdge next_edge;
//	while (m_open_set.size())
//	{
//		// Bring in smallest open set cost
//		next_edge = m_open_set.useTop();
//
//		// If not already in closed set
//		if (m_closed_set.find(next_edge.getNode()) == m_closed_set.end())
//		{
//			addToClosedSet(next_edge);
//			prim.push_back(next_edge);
//
//			// Check if found complete tree
//			if (m_closed_set.size() == graph.getNumVertices())
//			{
//				int total_edge(0);
//				for (auto it = m_closed_set.begin(); it != m_closed_set.end(); it++)
//				{
//					total_edge += it->second.first;
//				}
//				return pair<deque<PathEdge>, int>(prim, total_edge);
//			}
//		}
//	}
//	// Tree does not exist, return -1
//	deque<PathEdge> dummy_path;
//	dummy_path.emplace_back(PathEdge(-1, -1, -1));
//	return pair<deque<PathEdge>, int>(dummy_path, -1);
//}

void GraphAlgos::addToClosedSet(PathEdge next_edge)
{
	Node* next_node = next_edge.getNode();
	int next_edge_cost = next_edge.getCost();
	Node* next_prev_node = next_edge.getPrevNode();

	auto val = pair<int, Node*>(next_edge_cost, next_prev_node);
	m_closed_set.insert(map<Node*, pair<int, Node*>>::value_type(next_node, val));
	last_node = next_node;
}

void GraphAlgos::addNeighborsToOpenSet(Node* node, int add_edge_val)
{
	vector<Node*> nb = node->getNeighbors();
	int node_to_neighbor_cost = 1; // All neighbors same distance
	for (auto v : nb)
	{
		if (m_closed_set.find(v) == m_closed_set.end() && v->getColor() == node->getColor())
		{
			m_open_set.insert(PathEdge(v, add_edge_val + node_to_neighbor_cost, last_node));
		}
	}
}

void GraphAlgos::reset()
{
	m_closed_set.clear();
	m_open_set.clear();
}