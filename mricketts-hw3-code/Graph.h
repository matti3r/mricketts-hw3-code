/**
 * Author: Matthew Ricketts
 * File: Graph.h
 * Project: CS210 Homework 3
 * Date: 4/4/2022
 * Excerpt: Graph and shortest path implementation
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

using namespace std;

struct EdgeNode {
	string name;
	int y;
	int weight;
	struct EdgeNode* next;

	EdgeNode(string name = nullptr, int y = 0, int weight = 0, EdgeNode* next = nullptr)
		: name{ name }, y{ y }, weight{ weight }, next{ next } { }
};

class Graph {

private:
	static const int MAXV = 20;
	EdgeNode* edges[MAXV + 1] = {};

public:

	/**
	 * Constructor for the graph
	 */
	Graph() 
	{
		for (int k = 0; k <= MAXV; k++) {
			edges[k] = new EdgeNode("", k, 0, nullptr);
		}
	}

	/**
     * Destructor for the graph
     */
	~Graph() {}

	/**
	 * Associates the name with node i
	 */
	void name(int i, string name) {

		// Maximum of 21 nodes, all represented somewhere in edges array
		edges[i]->name = name;

		// CHECK FOR OTHER INSTANCES OF I
		// For every source node
		for (int k = 0; k <= MAXV; k++) {

			// Temp EdgeNode to scan for all other instances of i
			EdgeNode* temp = edges[k]->next;

			// Look through all its destination nodes
			while (temp != nullptr) {

				// If another link is found, name it and break to continue looking
				if (temp->y == i) {
					temp->name = name;
					break;
				}

				temp = temp->next;					// Check the next node's destination

			}
		}
	}

	/**
	 * Add an edge from i to j with weight d 
	 */
	void link(int i, int j, int d) {

		// CONSTRUCT A NEW EDGENODE
		// Give it all the info of edgeNode j, and the weight of the link
		// Insert it at the top of the list of nodes i is pointing to so O(1)
		// Point j to the previous top link under node i
		EdgeNode* newEdge = new EdgeNode(edges[j]->name, edges[j]->y, d, edges[i]->next);
		edges[i]->next = newEdge;

	}

	/**
	 * Delete edge i, j if one exists
	 */
	void deleteEdge(int i, int j) {

		// Temp EdgeNode to scan i's destinations
		EdgeNode* temp = edges[i];

		// Scan all of the destination nodes of i for j
		while (temp->next != nullptr) {

			unsigned int cnt = 0;

			if (temp->next->y == j) {

				// Bypass the previous connection
				EdgeNode* toDelete = temp->next;
				temp->next = temp->next->next;

				// Deallocate the memory of this edge and instance of j
				delete toDelete;

				// Link to j found, break the loop
				break;
			}

			if (cnt == 20){
				cout << "\nLink does not exist\n";
				break;
			}

				
		}

	}


	/**
	 * Prints a listing of all edges in the graph
	 * Each edge is listed as: name of  source node, name of destination node, distance between the two
	 */
	void dump() {

		// PRINT ALL EDGENODES
		cout << "From:\tTo:\tWeight:\n";

		// For every source node
		for (int i = 0; i <= MAXV; i++) {

			// Temp EdgeNode to scan i's destinations
			EdgeNode* temp = edges[i]->next;

			// Look through all its destination nodes
			while (temp != nullptr) {
				cout << edges[i]->name << "(" << edges[i]->y << "),\t" << temp->name << "(" << temp->y << "),\t" << temp->weight << endl;

				temp = temp->next;					// Check the next node's destination
			}

		}
	}

	/**
	 * Print the shortest path from s to g
	 * Uses Dijkstra's single source shortest path algorithm
	 */
	void path(int s, int g)
	{
		int dist[MAXV+1];			// The output array. dist[k] will hold the shortest distance from src to k
		int prev[MAXV+1];			// Array to hold the node right before the current node gets finalized
		bool finalized[MAXV+1];		// nodeProcessed[k] will be true if vertex k is included in shortest path tree or shortest distance from src to k is finalized


		// Initialize all distances as INFINITE and finalized[] as false
		for (int k = 0; k <= MAXV; k++) {
			dist[k] = INT_MAX;
			prev[k] = -1;
			finalized[k] = false;
		}

		// Distance of source vertex from itself is always 0
		dist[s] = 0;

		// Find shortest path for all vertices
		for (int k = 0; k < MAXV; k++) {

			// Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
			int u = minDistance(dist, prev, finalized);

			// Mark the picked vertex as processed
			finalized[u] = true;

			// Update dist value of the adjacent vertices of the picked vertex.
			EdgeNode* temp = edges[u];
			while (temp) {

				// Update dist[v] only if is not in nodeProcessed, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
				if (!finalized[temp->y] && dist[u] != INT_MAX && dist[u] + temp->weight < dist[temp->y]) {
					dist[temp->y] = dist[u] + temp->weight;
				}
					
				if (temp->next == nullptr)
					prev[temp->y] = temp->y;

				temp = temp->next;
			}
		}

		// print the constructed distance array
		printSolution(dist);

		// Print the shortest path
		cout << "\nThe shortest path from " << s << " to " << g << " is: " << dist[g] << endl << endl;
	}

	// Function to find the vertex with minimum distance value from the set of vertices not yet included in shortest path tree
	int minDistance(int dist[], int prev[], bool finalized[])
	{

		// Initialize min value
		int min = INT_MAX, min_index;

		for (int k = 0; k <= MAXV; k++)
			if (finalized[k] == false && dist[k] <= min)
				min = dist[k], min_index = k;

		return min_index;
	}

	// Debugger, print constructed distance array
	void printSolution(int dist[])
	{
		cout << "Vertex \t Distance from Source" << endl;
		for (int i = 0; i <= MAXV; i++)
			if (dist[i] < INT_MAX)
				cout << edges[i]->name << " \t\t" << dist[i] << endl;
	}




	/**
	 * Prints all the "dead end" nodes in the network. A node is a “dead end” if it has an out-degree of zero.  
	 */
	void dend() {

		// Look for any source node in the array that does not have any destination nodes
		for (int i = 0; i <= MAXV; i++)
			if (edges[i]->next == nullptr)
				cout << edges[i]->y << ", " << edges[i]->name << endl;

	}

	/**
	 * Prints all the "inaccessible" nodes in the network. A node is “inaccessible” if it has an in-degree of zero. 
	 */
	void inacess() {

		// Array to populate with 1s for node numbers that are accessible
		int accessArray[MAXV + 1] = { 0 };

		// CHECK FOR INACCESSABILITY
		// For every source node
		for (int i = 0; i <= MAXV; i++) {

			// Temp EdgeNode to scan i's destinations
			EdgeNode* temp = edges[i]->next;

			// Look through all its destination nodes
			while (temp != nullptr) {				
				accessArray[temp->y] = 1;			// If a node is in the list of nodes below another node ...
													//     it is a destination and therefore has an in-degree ...
													//     assign it a value of 1

				temp = temp->next;					// Check the next node's destination
			}

		}

		// Print the inaccessible nodes
		for (int i = 0; i <= MAXV; i++)
			if (accessArray[i] == 0)
				cout << edges[i]->y << ", " << edges[i]->name << endl;


	}

	// Note: you may need more instance variables (ivars) here depending on your implementation

};

#endif