#include "Graph.h"
#include "GraphAlgos.h"
#include "PriorityQueue.h"
#include <iostream>
#include <deque>

using namespace std;

void calcAvePath(Graph graph)
{
	GraphAlgos galg(graph);
	double ave_path_length = 0.0;
	int num_paths = 0;
	for (int i = 1; i < graph.getNumVertices(); i++)
	{
		// Check for path
		pair<deque<int>, int> out = galg.findPath(0, i);
		deque<int> path = out.first;
		int cost = out.second;
		if (cost != 10) {
			int i = 0;
		}
		if(path[0] != -1)
		{
			// Incremental average
			num_paths++;
			ave_path_length += (cost - ave_path_length)/num_paths;
		}
	}

	std::cout << "The average path length for density " << graph.getDensity() <<
		" with " << graph.getNumVertices() << " vertices is " << ave_path_length << std::endl;

	return;
}

void minSpanTree(Graph graph)
{
	GraphAlgos algo(graph);
	pair<deque<PathEdge>, int> out = algo.findPrimTree();
	
	cout << "MSP Edges are: " << endl;
	for (auto edge : out.first)
	{
		cout << edge.get();
	}
	cout << endl;

	cout << "MSP Cost is: " << out.second << endl;

	return;
}

int main()
{
	int a = 2, b = -3, c = 2;
	auto d = c % 5 / 2;
	auto e = -a * c++;
	char f = 'b';
	f += 2;
	vector<int> data(5, 1);

	// Create graph from file
	Graph graph("nodeData.txt");
	minSpanTree(graph);

	// Create graphs
	int num_vertex = 50;
	Graph graph20(num_vertex);
	Graph graph40(num_vertex);
	// Create one graph with density 0.2 and range 1-10
	// Create other grpah with density 0.4 and range 1-10
	graph20.createEdges(0.2, 10);
	graph40.createEdges(0.4, 10);


	calcAvePath(graph20);
	calcAvePath(graph40);

	return 0;
}