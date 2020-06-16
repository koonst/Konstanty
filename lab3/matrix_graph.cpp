#include "matrix_graph.h"

static int s_infinity = 1000000; //should be the same as in bellmanAlogrithms.cpp

static int s_balance_of_interval = -1; //balance for rand() in the fill method - interval is set
										//to 20 digits (0 - 19) originally. Using this variable you 
										//can manipulate it. For example changing to (-1) interval will be set to 
										//(-1 - 18)


MatrixGraph::MatrixGraph(int t_V, double t_density)
	: Graph(t_V, static_cast<int>(t_density* t_V* (t_V - 1)), t_density), 
	matrix(std::make_unique<std::unique_ptr<int[]>[]>(t_V)) {

	
	for (int iCell = 0; iCell < m_V; ++iCell) {

		matrix[iCell] = std::make_unique<int[]>(t_V);
		for (int iColumn = 0; iColumn < m_V; ++iColumn) {

			if (iCell == iColumn) matrix[iCell][iColumn] = 0; 
			else matrix[iCell][iColumn] = s_infinity; 
		}
	}
}


void MatrixGraph::fillGraph(const bool t_allowLoops) const {

	if (m_density == 1) { 
		for (int iRows = 0; iRows < m_V; ++iRows) { 
			for (int jColumns = 0; jColumns < m_V; ++jColumns) { 
				if (iRows != jColumns) 
				{
					int foo_weight = rand() % 20 + s_balance_of_interval;
					while (foo_weight == 0) { 

						foo_weight = rand() % 20 + s_balance_of_interval;
					}
					matrix[iRows][jColumns] = foo_weight;
				}
			}
		}
	}
	else { 

		int foo_edges = m_E;

		while (foo_edges) {

			int rowNode = rand() % m_V; 
			int columnNode = rand() % m_V;

			
			if (matrix[rowNode][columnNode] == 0 || matrix[rowNode][columnNode] == s_infinity) {

				int foo_weight = rand() % 20 + s_balance_of_interval;
				while (foo_weight == 0) { 

					foo_weight = rand() % 20 + s_balance_of_interval;
				}

				//detect if program want to crete a loop-edge to the same node
				//if user specified allowLopps = true, it will be created, if false,
				//iteration will be skipped and will not create any edge
				if (rowNode != columnNode) {

					matrix[rowNode][columnNode] = foo_weight;
					--foo_edges;
				}
				else if (t_allowLoops) {

					matrix[rowNode][columnNode] = foo_weight;
					--foo_edges;
				}
			}
		}
	}
}


void MatrixGraph::printGraph() const {

	std::cout << std::string(33, '-') << "\n  AdjencyMatrix Representation\n\n ";

	
	for (int iIter = 0; iIter < m_V; ++iIter) {

		if (iIter <= 10) std::cout << "    " << iIter;
		else if (iIter <= 100) std::cout << "   " << iIter;
		else std::cout << "  " << iIter;
	}
	std::cout << "\n\n";

	
	for (int iRows = 0; iRows < m_V; ++iRows) {

		
		if (iRows < 10) std::cout << iRows << "   |";
		else if (iRows < 100) std::cout << iRows << "  |";
		else std::cout << iRows << " |";

		
		for (int jColumns = 0; jColumns < m_V; ++jColumns) {

			int foo = matrix[iRows][jColumns];

			if (foo == s_infinity) std::cout << "*"; // if node is set to "infinity" then print a star 
			else std::cout << foo;					// as a symbol of no connection

			if (abs(foo) < 10 || abs(foo) == s_infinity) std::cout << "    "; //1000000 counts as a star so single digit space
			else if (abs(foo) < 100) std::cout << "   ";
			else std::cout << "  ";

			if (foo < 0) std::cout << '\b'; 
		}
	
		std::cout << "|\n";
	}
	std::cout << std::endl;
}



const int MatrixGraph::readFromFile() {

	std::ifstream file("Input.txt");
	if (!file.is_open()) {
		throw "INPUT MATRIX NOT OPEN!";
		return 1;
	}

	
	int start, source, destination, weight;
	file >> m_E >> m_V >> start;
	matrix = std::make_unique<std::unique_ptr<int[]>[]>(m_V);

	
	for (int iRow = 0; iRow < m_V; ++iRow) {

		matrix[iRow] = std::move(std::make_unique<int[]>(m_V));
		for (int iColumn = 0; iColumn < m_V; ++iColumn) {

			if (iRow == iColumn) matrix[iRow][iColumn] = 0;
			else matrix[iRow][iColumn] = s_infinity;
		}
	}


	for (int iEdge = 0; iEdge < m_E; ++iEdge) {

		file >> source >> destination >> weight;
		matrix[source][destination] = weight;;
	}
	file.close();
	return start; 
}



void MatrixGraph::createInput(const int t_startNode) const {

	std::ofstream file("CreatedInput.txt");
	if (!file.is_open()) {
		throw  "CREATED INPUT MATRIX NOT OPEN!";
		return;
	}

	file << m_E << " " << m_V << " " << t_startNode << "\n";
	for (int iRow = 0; iRow < m_V; ++iRow) {
		for (int iColumn = 0; iColumn < m_V; ++iColumn) {

			if (matrix[iRow][iColumn] != s_infinity && matrix[iRow][iColumn] != 0) {

				file << iRow << " ";
				file << iColumn << " ";
				file << matrix[iRow][iColumn] << "\n";
			}
		}
	}
	file.close();
}
