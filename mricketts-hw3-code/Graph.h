#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>


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
		EdgeNode* temp = edges[i]->next;

		// Scan all of the destination nodes of i for j
		while (temp->next != nullptr) {
			if (temp->next->y == j) {

				// Bypass the previous connection
				EdgeNode* toDelete = temp->next;
				temp->next == temp->next->next;

				// Deallocate the memory of this edge and instance of j
				delete toDelete;
				
				// Link to j found, break the loop
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
		// For every source node
		for (int i = 0; i <= MAXV; i++) {

			// Temp EdgeNode to scan i's destinations
			EdgeNode* temp = edges[i]->next;

			// Look through all its destination nodes
			while (temp != nullptr) {
				cout << edges[i]->name << ", " << temp->name << ", " << temp->weight << endl;

				temp = temp->next;					// Check the next node's destination
			}

		}
	}

	/**
	 * Print the shortest path from s to g
	 */
	void path(int s, int g) {


		/*
			*********        *********        *         *                *                		
		    *                    *            *         *                *
		    *					 *            *         *                *
		    *					 *            *         *                *
		    *********			 *            *         *                *
		            *			 *            *         *                *
		            *			 *            *         *                *
		            *			 *            *         *                *
		    *********			 *            *         *********        *********
		*/



	}
	
	/**
	 * Prints all the "dead end" nodes in the network. A node is a “dead end” if it has an out-degree of zero.  
	 */
	void dend() {

		// Look for any source node in the array that does not have any destination nodes
		for (int i = 0; i <= MAXV; i++)
			if (edges[i]->next == nullptr)
				cout << (edges[i]->name);

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