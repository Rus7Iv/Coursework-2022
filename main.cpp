#include "Graph.h"
#include <omp.h>
#include <iostream> 

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	omp_set_num_threads(4);

#ifdef _OPENMP 
	cout << "OpenMP support\n";
#endif

	int countVertices, countEdges;
	cout << "Введите количество узлов:";
	cin >> countVertices;
	cout << endl;

	cout << "Введите количество рёбер:";
	cin >> countEdges;
	cout << endl;

	Graph graph(countVertices);

	cout << "Создание графа..." << endl;
	graph.createGraph(graph, countEdges);

	graph.printGraph();
	cout << endl;

	cout << "Максимальный разрез графа: " << endl;
	graph.findMaxCut();

	system("pause");
	return 0;
}