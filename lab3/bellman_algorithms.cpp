#include "bellman_algorithms.h"

static int  s_infinity = 1000000; //because of the small interval in which weight of the edge can be created
static int  s_neg_infinity = -1000000;	//it is ok to set inf to the one million. If you want to make this
										//interval bigger, you should also change this static variable to a bigger one
										//otherwise program might not work properly for bigger number of vertices


void finalSolution(std::string t_pathArr[], int t_dist[], int t_n, int t_startNode) {

	std::ofstream file("Output.txt");

	std::cout << std::string(20, '-') << "\n   FinalSolution\n\n";
	std::cout << "The starting node was -> " << t_startNode << "\n\n";

	file << std::string(20, '-') << "\n   FinalSolution\n\n";
	file << "The starting node was -> " << t_startNode << "\n\n";

	for (int i = 0; i < t_n; ++i) {

		if (t_dist[i] == s_neg_infinity) {
			std::cout << i << "->" << "-inf\n";
			file << i << "->" << "-inf\n";
			continue; 
		}																
		else if (t_dist[i] == s_infinity) {
			std::cout << i << "->" << "inf\n";
			file << i << "->" << "inf\n";
			continue; 
		}
		
		else {
			std::cout << i << "->" << t_dist[i];
			file << i << "->" << t_dist[i];
		}

		

		//first block: regarding number of source node
		if (i < 10) {
			std::cout << "   ";
			file << "   ";
		}
		else if (i < 100) {
			std::cout << "  ";
			file << "  ";
		}
		else {
			std::cout << " ";
			file << " ";
		}

		//second block: regarding shortest distance
		if ((t_dist[i] >= 100 && t_dist[i] < 1000) || (-100 > t_dist[i] && t_dist[i] <= -10)) {

			std::cout << " The shortest path: " << t_pathArr[i] << i;
			file << " The shortest path: " << t_pathArr[i] << i;
		}
		else if (0 <= t_dist[i] && t_dist[i] < 10) {

			std::cout << "   The shortest path: " << t_pathArr[i] << i;
			file << "   The shortest path: " << t_pathArr[i] << i;
		}
		else if ((t_dist[i] >= 10 && t_dist[i] < 100) || (-10 < t_dist[i] && t_dist[i] < 0)) {

			std::cout << "  The shortest path: " << t_pathArr[i] << i;
			file << "  The shortest path: " << t_pathArr[i] << i;
		}
		else { //in case of emergency add another interval: (-1000,-100] || [1000,10000)

			std::cout << "The shortest path: " << t_pathArr[i] << i;
			file << "The shortest path: " << t_pathArr[i] << i;
		}
		std::cout << std::endl;
		file << std::endl;
	}
	std::cout << std::endl;
	file.close();
}


//bellmanFord for adjencyList
double bellmanFord(std::shared_ptr<ListGraph> t_graph, int t_startNode, bool t_printSolution) {

	std::string* storePath = new std::string[t_graph->getV()]; //storage for path strings 

	auto t_start = std::chrono::high_resolution_clock::now(); 

	int* storeDistance = new int[t_graph->getV()]; //storage for shotrtest distances

	for (int iCell = 0; iCell < t_graph->getV(); ++iCell) {

		storeDistance[iCell] = s_infinity; //init all distances with inf
	}

	storeDistance[t_startNode] = 0; //and source one with 0

	for (int i = 1; i < t_graph->getV(); ++i) { 
		for (int j = 0; j < t_graph->getE(); ++j) {

			int u = t_graph->getStruct()[j].source;
			int v = t_graph->getStruct()[j].dest;
			int weight = t_graph->getStruct()[j].weight;

			if (storeDistance[u] + weight < storeDistance[v]) {
				storeDistance[v] = storeDistance[u] + weight;

				if (t_printSolution) {  

					storePath[v].clear();
					storePath[v].append(storePath[u] + std::to_string(u) + "->");
				}
			}
		}
	}

	//checking for negative cycles right now
	for (int i = 1; i < t_graph->getV(); ++i) {
		for (int j = 0; j < t_graph->getE(); ++j) {

			int u = t_graph->getStruct()[j].source;
			int v = t_graph->getStruct()[j].dest;
			int weight = t_graph->getStruct()[j].weight;
			if (storeDistance[u] + weight < storeDistance[v]) {

				if (storeDistance[u] > s_infinity / 2) storeDistance[u] = s_infinity;  //protection from adding negative inf- 
				else storeDistance[v] = s_neg_infinity;				//-when the node is disconnected from the source anyway
			}
			else if (storeDistance[u] > s_infinity / 2) storeDistance[u] = s_infinity;  //after first part of the algorithm
						//if there was a negative cycle, and this (j) node is disconnected from the source then distances
						//are going to be corrupted and instead of infinity (1000000) there will be something like 9999992. 
						//thats why we need to manually set it to infinity. This is done by detecting > inf/2 so the the corrupted
						//distance sholud be interpreted correctly and not confused with huge (correct) distance. On the other
						//hand corrupted distance can also reach huge negative amount and mess it up either way. Thats why its 						
						//best to distinguish this event by the middle value of infinity.
		}
	}
	auto t_end = std::chrono::high_resolution_clock::now(); //stop clock

	
	if (t_printSolution) finalSolution(std::move(storePath), std::move(storeDistance), t_graph->getV(), t_startNode);
	delete[] storeDistance;
	delete[] storePath;
	return std::chrono::duration<double, std::milli>(t_end - t_start).count(); //return the time difference
}



double bellmanFord(std::shared_ptr<MatrixGraph> t_graph, int t_startNode, bool t_printSolution) {

	std::string* storePath = new std::string[t_graph->getV()];

	auto t_start = std::chrono::high_resolution_clock::now();

	int* storeDistance = new int[t_graph->getV()];

	for (int iCell = 0; iCell < t_graph->getV(); ++iCell) {

		storeDistance[iCell] = s_infinity;
	}

	storeDistance[t_startNode] = 0;

	for (int i = 1; i < t_graph->getV(); ++i) {
		for (int j = 0; j < t_graph->getV(); ++j) {
			for (int w = 0; w < t_graph->getV(); ++w) {

				int u = j;
				int v = w;
				int weight = t_graph->getWeight(j, w);
				if (storeDistance[u] + weight < storeDistance[v]) {

					storeDistance[v] = storeDistance[u] + weight;
					if (t_printSolution) {

						storePath[v].clear();
						storePath[v].append(storePath[u] + std::to_string(u) + "->");
					}
				}
			}
		}
	}
	for (int i = 1; i < t_graph->getV(); ++i) {
		for (int j = 0; j < t_graph->getV(); ++j) {
			for (int w = 0; w < t_graph->getV(); ++w) {

				int u = j;
				int v = w;
				int weight = t_graph->getWeight(j, w);
				if (storeDistance[u] + weight < storeDistance[v]) {

					if (storeDistance[u] > s_infinity / 2) storeDistance[u] = s_infinity;
					else if (weight == s_infinity) continue; 
					else storeDistance[v] = s_neg_infinity;
				}
				else if (storeDistance[u] > s_infinity / 2) storeDistance[u] = s_infinity;
			}
		}
	}
	auto t_end = std::chrono::high_resolution_clock::now();

	if (t_printSolution) finalSolution(std::move(storePath), std::move(storeDistance), t_graph->getV(), t_startNode);
	delete[] storeDistance;
	delete[] storePath;
	return std::chrono::duration<double, std::milli>(t_end - t_start).count();
}
