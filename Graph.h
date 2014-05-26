#pragma once
#include "Node.h"
#include <algorithm>
#define MAP_SIZE 20

using namespace std;

class Graph
{
public:
	Graph();
	void setStart(int, int);
	void setDestination(int, int);
	void setWall(int x, int y) { map[x][y]->type = Node::Type::Wall; }
	void setEdges();
	bool visitNodes();
	void print();
private:
	Node* map[MAP_SIZE][MAP_SIZE];
	vector<Node*> unvisitedNodes;
	Node* start;
	Node* destination;
	Node* current;
};

Graph::Graph()
{
	unsigned lastId = 0;
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		for (int j = 0; j < MAP_SIZE; ++j)
		{
			map[i][j] = new Node();
			map[i][j]->id = lastId; //Set a unique ID for each node, used later for removing from the unvisited node list
			++lastId;
			unvisitedNodes.push_back(map[i][j]);
		}
	}
}

void Graph::setStart(int x, int y)
{
	start = map[x][y];
	start->type = Node::Type::Start;
	start->distance = 0;
	current = start;
}

void Graph::setDestination(int x, int y)
{
	destination = map[x][y];
	destination->type = Node::Type::Destination;
}

//Sets the edges between the nodes. Diagonal movement allowed (root(2) length)
void Graph::setEdges()
{
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		for (int j = 0; j < MAP_SIZE; ++j)
		{
			Node::Type wall = Node::Type::Wall;
			if (j + 1 < MAP_SIZE && map[i][j + 1]->type != wall)	//right node
				map[i][j]->neighbors.push_back({ map[i][j + 1], 1 });
			if (j > 0 && map[i][j - 1]->type != wall)				//left node
				map[i][j]->neighbors.push_back({ map[i][j - 1], 1 });
			if (i + 1 < MAP_SIZE && map[i + 1][j]->type != wall)	//below node
				map[i][j]->neighbors.push_back({ map[i + 1][j], 1 });
			if (i > 0 && map[i - 1][j]->type != wall)				//above node
				map[i][j]->neighbors.push_back({ map[i - 1][j], 1 });

			if (j + 1 < MAP_SIZE && i > 0 && map[i - 1][j + 1]->type != wall)				//right above node
				map[i][j]->neighbors.push_back({ map[i - 1][j + 1], 1.414 });
			if (j + 1 < MAP_SIZE && i + 1 < MAP_SIZE && map[i + 1][j + 1]->type != wall)	//right below node
				map[i][j]->neighbors.push_back({ map[i + 1][j + 1], 1.414 });
			if (j > 0 && i > 0 && map[i - 1][j - 1]->type != wall)							//left above node
				map[i][j]->neighbors.push_back({ map[i - 1][j - 1], 1.414 });
			if (j > 0 && i + 1 < MAP_SIZE && map[i + 1][j - 1]->type != wall)				//left below node
				map[i][j]->neighbors.push_back({ map[i + 1][j - 1], 1.414 });
		}
	}
}

//Visits the nodes in the graph. Returns true if we reach the destination node
bool Graph::visitNodes()
{
	if (current == NULL) return false; //Return false if we can't reach our destination (no more nodes in the unvisited list)

	for (vector<Node::Edge>::iterator it = current->neighbors.begin(); it != current->neighbors.end(); ++it) //Look at the current node's neighbors
	{
		double distance = current->distance + it->length;
		if (!it->node->visited && distance < it->node->distance) //If a new tentative distance is smaller than that neighbor's current saved distance, replace it
		{
			it->node->distance = distance;
			it->node->previous = current;
		}
	}

	current->visited = true;
	vector<Node*>::iterator it = std::find(unvisitedNodes.begin(), unvisitedNodes.end(), current);
	if (it != unvisitedNodes.end()) unvisitedNodes.erase(it); //Remove the current node from the unvisited list
	
	if (destination->visited)
	{
		for (Node* path = destination->previous; path != start; path = path->previous)
			path->type = Node::Type::Path; //Mark all nodes along the path from destination to start
		return true; //Return true because we've reached our destination
	}
	else
	{
		Node* smallestNode = NULL;
		double smallestDistance = INT_MAX;
		for (vector<Node*>::iterator it = unvisitedNodes.begin(); it != unvisitedNodes.end(); ++it) //Look for the node in the unvisited list with the smallest distance
		{
			if ((*it)->distance < smallestDistance)
			{
				smallestNode = *it;
				smallestDistance = smallestNode->distance;
			}
		}
		current = smallestNode; //Set our new current node as that smallest distance node
		return visitNodes(); //Visit nodes again
	}
}

void Graph::print()
{
	for (int j = 0; j < MAP_SIZE; ++j)
	{
		for (int i = 0; i < MAP_SIZE; ++i)
		{
			char c;
			switch (map[i][j]->type)
			{
			case Node::Type::Start:
				c = 'S'; break;
			case Node::Type::Destination:
				c = 'D'; break;
			case Node::Type::Normal:
				c = '-'; break;
			case Node::Type::Path:
				c = '*'; break;
			case Node::Type::Wall:
				c = 'W'; break;
			}
			cout << c << " ";
		}
		cout << endl;
	}
	cout << endl;
}
