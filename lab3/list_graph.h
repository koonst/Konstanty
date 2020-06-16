#pragma once

#include "graph.h"

//represents weighted edge between two nodes
struct Edge {

	
	int source, dest, weight;
};



class ListGraph : public Graph {

	Edge* edge; 

public:

	void fillGraph(const bool allowLoops) const override;
	void printGraph() const override;
	const int readFromFile() override;
	void createInput(const int t_startNode) const override;

	const Edge* getStruct() const { return edge; }
	void addEdge(int t_guardNumber, int t_number, int t_weight, int flag) const;
	bool detectIfExist(int t_guardNumber, int t_nodeNumber) const;

	explicit ListGraph(int t_V, double t_density)
		:Graph(t_V, static_cast<int>(t_density* t_V* (t_V - 1)), t_density),
		edge(new Edge[static_cast<int>(t_density * t_V * (t_V - 1))]) {}
	ListGraph() : Graph() {};
	~ListGraph() { delete[] edge; }
};