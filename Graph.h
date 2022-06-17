#pragma once
#include <list> 
using namespace std;

// Класс Graph представляет собой ориентированный граф, использующий представление списка смежности
class Graph
{
	int numberVertices;
	list<int>* adjMatrix;// Указатель на массив, содержащий списки смежности
public:
	Graph();
	Graph(int numberVertices);
	bool addEdge(int numberVertices, int numberEdges);
	void createGraph(Graph& graph, int M);
	void connections(int w, bool visited[], int dis[], int low[], int par[]);
	void findMaxCut();
	void printGraph(); //вывод графа на экран
};
