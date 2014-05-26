#include <iostream>
#include "Node.h"
#include "Graph.h"

using namespace std;


int main()
{
	Graph graph;

	graph.setStart(1, 10);
	graph.setDestination(18, 4);
	for (int y = 0; y < 17; ++y) graph.setWall(4, y);
	for (int x = 8; x < 19; ++x) graph.setWall(x, 11); //Change x upper bound to see different paths
	for (int y = 4; y < 11; ++y) graph.setWall(12, y);

	graph.setEdges();

	cout << "Unvisited graph:\n";
	graph.print();

	if (graph.visitNodes())
	{
		cout << "Visited graph:\n";
		graph.print();
	}
	else cout << "Could not find a path from start to destination.\n";

	system("PAUSE");
}