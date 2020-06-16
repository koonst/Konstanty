#pragma once

#include "graph.h" 

#include <cstdlib>
#include <memory>


class MatrixGraph : public Graph {

	std::unique_ptr<std::unique_ptr<int[]>[]> matrix; //dynamic array of dynamic arrays; 
														//main container of graph
public:
	
	void fillGraph(const bool allowLoops) const override;
	void printGraph() const override;
	const int readFromFile() override;
	void createInput(const int t_startNode) const override;

	
	const int& getWeight(int t_row, int t_column) const { return matrix[t_row][t_column]; }

	explicit MatrixGraph(int t_V, double t_density);
	MatrixGraph() : Graph() {};
};