#ifndef GRAPH_H
#define GRAPH_H

#include <string>

using namespace std;

struct EdgeNode {
	int y;
	int weight;
	struct EdgeNode* next;
};

class Graph {

private:
	static const int MAXV = 20;
	EdgeNode* edges[MAXV + 1] = {};

public:

	Graph() 
	{
	}

	/**
     * Destructor for the graph
     */
	~Graph() {}

	/**
	 * Associates the name with node i
	 */
	void name(int i, string name) {

	}

	/**
	 * Add an edge from i to j with weight d 
	 */
	void link(int i, int j, int d) {


	}

	/**
	 * Delete edge i, j if one exists
	 */
	void deleteEdge(int i, int j) {

	}


	/**
	 * Prints a listing of all edges in the graph
	 * Each edge is listed as: name of  source node, name of destination node, distance between the two
	 */
	void dump() {

	}

	/**
	 * Print the shortest path from s to g
	 */
	void path(int s, int g) {

	}
	
	/**
	 * Prints all the "dead end" nodes in the network. A node is a “dead end” if it has  an out-degree of zero.  
	 */
	void dend() {

	}

	/**
	 * Prints all the "inaccessible" nodes in the network. A node is “inaccessible” if it has an in-degree of zero. 
	 */
	void inacess() {

	}

	// Note: you may need more instance variables (ivars) here depending on your implementation

};

#endif