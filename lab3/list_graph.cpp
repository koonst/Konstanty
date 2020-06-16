#include "list_graph.h"

static int s_balance_of_interval = -1; //the same as in matrixGraph

void ListGraph::addEdge(int t_guardNumber, int t_number, int t_weight, int t_flag) const {

	edge[t_flag].dest = t_number;
	edge[t_flag].source = t_guardNumber;
	edge[t_flag].weight = t_weight;
}


bool ListGraph::detectIfExist(int t_guardNumber, int t_nodeNumber) const {

	for (int iNumber = 0; iNumber < m_E; ++iNumber) { //check whole list of edges

		if (edge[iNumber].dest == t_nodeNumber && edge[iNumber].source == t_guardNumber) return true;
	}
	return false;
}


void ListGraph::fillGraph(const bool t_allowLoops) const {

	if (m_density == 1) {

		int foo_flag = 0;
		for (int iSource = 0; iSource < m_V; ++iSource) {
			for (int iDest = 0; iDest < m_V; ++iDest) { 

				if (iSource != iDest) { 

					int foo_weight = rand() % 20 + s_balance_of_interval;
					while (foo_weight == 0) { 

						foo_weight = rand() % 20 + s_balance_of_interval;
					}
					addEdge(iSource, iDest, foo_weight, foo_flag++);
				}
			}
		}
	}
	else { 

		int foo_edges = 0;
		while (foo_edges < m_E) {

			int guardNode = rand() % m_V;
			int nodeNode = rand() % m_V;
			if (!detectIfExist(guardNode, nodeNode)) {

				int foo_weight = rand() % 20 + s_balance_of_interval;
				while (foo_weight == 0) {

					foo_weight = rand() % 20 + s_balance_of_interval;
				}

				if (guardNode != nodeNode) addEdge(guardNode, nodeNode, foo_weight, foo_edges++);
				else if (t_allowLoops) addEdge(guardNode, nodeNode, foo_weight, foo_edges++);
			}
		}
	}
}


void ListGraph::printGraph() const {

	std::cout << std::string(30, '-') << "\n  AdjencyList Representation\n\n";
	for (int iSource = 0; iSource < m_V; ++iSource) {

		
		std::cout << iSource;
		for (int iEdge = 0; iEdge < m_E; ++iEdge) {

			
			if (edge[iEdge].source == iSource)
				std::cout << "->" << "[" << edge[iEdge].dest << "|" << edge[iEdge].weight << "]";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}


const int ListGraph::readFromFile() {

	std::ifstream file("Input.txt");
	if (!file.is_open()) {
		throw "INPUT LIST NOT OPEN!";
		return 1;
	}

	
	int start, source, destination, weight;
	file >> m_E >> m_V >> start;
	edge = new Edge[m_E];

	//adding all connections
	for (int iEdge = 0; iEdge < m_E; ++iEdge) {

		file >> source >> destination >> weight;
		addEdge(source, destination, weight, iEdge);
	}
	file.close();
	return start; 
}



void ListGraph::createInput(const int t_startNode) const {

	std::ofstream file("CreatedInput.txt");
	if (!file.is_open()) {
		throw  "CREATED INPUT LIST NOT OPEN!";
		return;
	}

	file << m_E << " " << m_V << " " << t_startNode << "\n";
	for (int iEdge = 0; iEdge < m_E; ++iEdge) {

		file << edge[iEdge].source << " ";
		file << edge[iEdge].dest << " ";
		file << edge[iEdge].weight << "\n";
	}
	file.close();
}
