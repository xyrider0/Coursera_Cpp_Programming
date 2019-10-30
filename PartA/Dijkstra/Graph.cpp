#include "Graph.h"
#include <limits>

Graph::Graph(int num_vertices) : m_num_vertices(num_vertices), m_density(0.0), m_num_edges(0)
{
	vector<int> init(num_vertices, std::numeric_limits<int>::max());
	for (int i = 0; i < m_num_vertices; ++i)
	{
		m_conn_matrix.emplace_back(init);
	}
}

int Graph::getNumVertices()
{
	return m_num_vertices;
}

int Graph::getNumEdges()
{
	return m_num_edges;
}

int Graph::getEdgeValue(int v1, int v2)
{
	assert(v1 < m_num_vertices);
	assert(v2 < m_num_vertices);
	return m_conn_matrix[v1][v2];
}

bool Graph::isAdjacent(int v1, int v2)
{
	assert(v1 < m_num_vertices);
	assert(v2 < m_num_vertices);
	return m_conn_matrix[1][v2] == std::numeric_limits<int>::max() ? false : true;
}

// Assumes undirected graph
void Graph::addEdge(int v1, int v2, int edge_value)
{
	assert(v1 < m_num_vertices);
	assert(v2 < m_num_vertices);
	assert(edge_value > 0);
	if (m_conn_matrix[v1][v2] == std::numeric_limits<int>::max())
	{
		m_num_edges++;
		m_conn_matrix[v1][v2] = edge_value;
		m_conn_matrix[v2][v1] = edge_value;
	}

	return;
}

// Assumes undirected graph
void Graph::setEdge(int v1, int v2, int edge_value)
{
	assert(v1 < m_num_vertices);
	assert(v2 < m_num_vertices);
	assert(edge_value > 0);
	if (m_conn_matrix[v1][v2] != std::numeric_limits<int>::max())
	{
		m_conn_matrix[v1][v2] = edge_value;
		m_conn_matrix[v2][v1] = edge_value;
	}
}


// Assumes undirected graph
void Graph::deleteEdge(int v1, int v2)
{
	assert(v1 < m_num_vertices);
	assert(v2 < m_num_vertices);
	if (m_conn_matrix[v1][v2] != std::numeric_limits<int>::max())
	{
		m_num_edges--;
	}
	m_conn_matrix[v1][v2] = std::numeric_limits<int>::max();
	m_conn_matrix[v2][v1] = std::numeric_limits<int>::max();
}

void Graph::createEdges(double density, int range)
{
	m_density = density;
	uniform_int_distribution<int> edge_len_gen(1, range);
	uniform_real_distribution<double> prob_gen(0.0, 1.0);
	default_random_engine e(time(0));

	for (int i = 0; i < m_num_vertices; i++)
	{
		for (int j = i+1; j < m_num_vertices; j++)
		{
			if (prob_gen(e) < density)
			{
				int len = edge_len_gen(e);
				addEdge(i, j, edge_len_gen(e));
				m_num_edges++;
			}
		}
	}

	return;
}

vector<int> Graph::getNeighbors(int vert)
{
	vector<int> neighbors;
	for (int i = 0; i < m_num_vertices; ++i)
	{
		if (m_conn_matrix[vert][i] != std::numeric_limits<int>::max())
		{
			neighbors.push_back(i);
		}
	}
	return neighbors;
}

double Graph::getDensity()
{
	return m_density;
}