/**
 * Author: Matthew Ricketts
 * File: Source.cpp
 * Project: CS210 Homework 3
 * Date: 4/4/2022
 * Excerpt: Graph and shortest path menu
 */

#include <iostream>
#include <string>

#include "Graph.h"


// Function declaration
string toLower(string);
void debugFillGraph(Graph);

// Main function
int main() {

	
	Graph graph = Graph();

	//debugFillGraph(graph);

	string userMenuOption;

	cout << "\n\n\nThis program implements a graph.\n";

	do {

		cout << "\n\nWhat would you like to do:\n"
				"A: Add an edge.\n" <<
				"D: Delete an edge.\n" <<
				"N: Add a name to a node.\n" <<
				"P: Print all edges in network.\n" <<
				"SP: Find shortest path between two nodes.\n" <<
				"DE: List all the dead-end nodes.\n" <<
				"IN: List all the inaccessible nodes.\n" <<
				"E: exit\n\n";

		// Get user input
		cin >> userMenuOption;

		// Implement menu
		if ("a" == toLower(userMenuOption)) {
			int from, to, weight;

			// Get the nodes to link
			cout << "Add Edge\n";
			cout << "From Node: "; cin >> from;
			cout << "To Node: "; cin >> to;
			cout << "Weight: "; cin >> weight;


			// Link the nodes
			graph.link(from, to, weight);

			cout << "Edge Added";

		}
		else if ("d" == toLower(userMenuOption)) {
			int from, to;
			
			cout << "Remove Edge\n";
			cout << "From Node: "; cin >> from;
			cout << "To Node: "; cin >> to;

			graph.deleteEdge(from,to);

			cout << "Edge Removed";
		}
		else if ("n" == toLower(userMenuOption)) {
			int node;
			string name;

			cout << "Add Name to Node\n";
			cin.ignore();
			cout << "Name: "; getline(cin, name);
			cout << "Node: "; cin >> node;

			graph.name(node, name);

			cout << "Name Added";
		}
		else if ("p" == toLower(userMenuOption)) {
			graph.dump();
		}
		else if ("sp" == toLower(userMenuOption)) {
			int from, to;

			cout << "Find the Shortest Path\n";
			cout << "From Node: "; cin >> from;
			cout << "To Node: "; cin >> to;

			graph.path(from,to);
		}
		else if ("de" == toLower(userMenuOption)) {
			graph.dend();
		}
		else if ("in" == toLower(userMenuOption)) {
			graph.inacess();
		}
		else if ("e" != toLower(userMenuOption)) {
			cout << "Invalid Input";
		}


	} while (toLower(userMenuOption) != "e");

	
	return 0;
}


/**
*  Function to convert a string to lowercase
*  Param: toConvert, String to convert to lowercase
*/ 

string toLower(string toConvert) {

	for (unsigned int i = 0; i < toConvert.length(); i++)
	{
		toConvert[i] = tolower(toConvert[i]);
	}

	return toConvert;
}


void debugFillGraph(Graph graph) {
	graph.name(0, "A");
	graph.name(1, "B");
	graph.name(2, "C");
	graph.name(3, "D");
	graph.name(4, "E");
	graph.name(5, "F");
	graph.name(6, "G");

	graph.link(0, 1, 6);
	graph.link(0, 5, 10);
	graph.link(0, 6, 5);

	graph.link(1, 0, 6);
	graph.link(1, 5, 1);
	graph.link(1, 2, 9);

	graph.link(2, 1, 9);
	graph.link(2, 5, 7);
	graph.link(2, 3, 8);

	graph.link(3, 2, 8);
	graph.link(3, 4, 4);

	graph.link(4, 3, 4);
	graph.link(4, 2, 1);
	graph.link(4, 5, 7);
	graph.link(4, 6, 8);

	graph.link(5, 0, 10);
	graph.link(5, 1, 1);
	graph.link(5, 2, 7);
	graph.link(5, 4, 7);
	graph.link(5, 6, 3);

	graph.link(6, 1, 5);
	graph.link(6, 5, 3);
	graph.link(6, 4, 8);
}
