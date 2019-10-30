#pragma once
#include <vector>
#include <random>
#include <ctime>
#include <cassert>

using namespace std;

class Graph {
public:
	Graph(int num_vertices);

	void createEdges(double density, int range);

	int getNumVertices();
	int getNumEdges();
	double getDensity();

	bool isAdjacent(int v1, int v2);
	vector<int> getNeighbors(int vert);

	void addEdge(int v1, int v2, int edge_value = 1); // Does not overwrite existing edge
	void setEdge(int v1, int v2, int edge_value = 1);
	int getEdgeValue(int v1, int v2);
	void deleteEdge(int v1, int v2);

private:
	int m_num_vertices;
	int m_num_edges;
	double m_density;
	vector<vector<int>> m_conn_matrix;
};