#include "Graph.h"
#include "ShortestPath.h"
#include "PriorityQueue.h"
#include <iostream>
#include <deque>

using namespace std;

void calcAvePath(Graph graph)
{
	ShortestPath spath(graph);
	double ave_path_length = 0.0;
	int num_paths = 0;
	for (int i = 1; i < graph.getNumVertices(); i++)
	{
		// Check for path
		pair<deque<int>, int> out = spath.findPath(0, i);
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

int main()
{
	// Create graphs
	int num_vertex = 50;
	Graph graph20(num_vertex);
	Graph graph40(num_vertex);
	Graph graph100(num_vertex);
	// Create one graph with density 0.2 and range 1-10
	// Create other grpah with density 0.4 and range 1-10
	//graph20.createEdges(0.2, 1);
	//graph40.createEdges(0.4, 1);
	graph100.createEdges(1.0, 10);


	calcAvePath(graph20);
	calcAvePath(graph40);
	calcAvePath(graph100);

	return 0;
}