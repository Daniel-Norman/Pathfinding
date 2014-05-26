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

	Node();
	vector<Edge> neighbors;
	Node* previous;
	bool operator==(Node*);


	double distance;
	Type type;
	bool visited;
	unsigned id;
};

Node::Node() : previous(NULL), distance(INT_MAX), type(Normal), visited(false) { }

bool Node::operator==(Node* other)
{
	return this->id == other->id;
}