#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>



class Graph {

protected:
	int m_V, m_E; //amount of Vertices and Edges
	double m_density;

public:
	const int& getV() const { return m_V; }
	const int& getE() const { return m_E; }

	virtual void fillGraph(const bool allowLoops) const = 0;
	virtual void printGraph() const = 0;
	virtual const int readFromFile() = 0;
	virtual void createInput(const int t_startNode) const = 0;
													
	virtual ~Graph() {};
	explicit Graph(int t_V, int t_E, double t_density) : m_V(t_V), m_E(t_E), m_density(t_density) {}
	Graph() {}; 
};				