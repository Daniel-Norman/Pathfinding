#pragma once
#include <vector>
#include <climits>

using namespace std;

class Node
{
public:
	struct Edge
	{
		Node* node;
		double length;
	};
	enum Type{ Normal, Wall, Start, Destination, Path };

	Node(int, int);
	vector<Edge> neighbors;
	Node* previous;
	bool operator==(Node*);


	double distance, heuristic;
	Type type;
	bool visited;
	int x, y;
};

Node::Node(int x, int y) : previous(NULL), distance(INT_MAX), type(Normal), visited(false), x(x), y(y), heuristic(0) { }

bool Node::operator==(Node* other)
{
	return this->x == other->x && this->y == other->y;
}