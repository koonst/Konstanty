#include <time.h>

#include "bellman_algorithms.h"


//function that conducts test

template<typename T>
std::ostream& tests(std::ostream& file, int(&vertTab)[5], double(&densTab)[4], int loops) {

	for (double density : densTab) { 
		for (int vertices : vertTab) { 
			double sum = 0;
			for (int iLoops = 0; iLoops < loops; ++iLoops) { 

				std::shared_ptr<T> graph = std::make_shared<T>(vertices, density);
				int startNode = rand() % vertices;

				graph->fillGraph(true);

				sum += bellmanFord(std::move(graph), startNode, false);
				std::cout << (iLoops * 100 / loops) + 1 << "%" << "\r" << std::flush;
			}
			file << sum / loops << " "; 
			std::cout << vertices << " VERTICES DONE!" << std::endl;
		}
		std::cout << "\n" << density << " DENISTY DONE!\n" << std::endl;
	}
	file << "\n";
	return file;
}


int main() {

	srand(static_cast<unsigned int>(time(NULL)));

	bool testZone = true;

	if (testZone) 
	{

		//////////////////////////
		int vertTab[5] = { 5, 15, 30, 50, 100 };
		double densTab[4] = { 0.25, 0.5, 0.75, 1 };
		int loops = 100;		
		/////////////////////////

		std::ofstream file("OutputTimes.txt");
		if (!file.is_open()) 
		{

			std::cerr << "OUTPUT TIMES NOT OPEN!" << std::flush;
			return 1;
		}

		tests<ListGraph>(file, vertTab, densTab, loops);
		std::cout << "LIST DONE\n" << std::endl;
		tests<MatrixGraph>(file, vertTab, densTab, loops);
		std::cout << "MATRIX DONE" << std::endl;

		file.close();
		return 0;
	}
	return 0;
}