#include "Graph.h"
#include <omp.h>
#include<iostream> 
#include <list> 
#include <set>

omp_lock_t lock;

using namespace std;

Graph::Graph()
{
    this->numberVertices = 1;
    this->adjMatrix = new list<int>[numberVertices];
}


Graph::Graph(int numberVertices)
{
    this->numberVertices = numberVertices;
    this->adjMatrix = new list<int>[numberVertices];
}

bool Graph::addEdge(int v, int w)
{
    if (v < this->numberVertices && v > -1 && w < this->numberVertices && w > -1) {
        if (v != w) {
            this->adjMatrix[v].push_back(w);
            this->adjMatrix[w].push_back(v);
        }
        else {
            this->adjMatrix[v].push_back(w);
        }
        return true;
    }
    else {
        return false;
    }
}

void Graph::connections(int currentVertice, bool visited[], int dis[], int low[], int par[]) {
    static int t = 0;
    visited[currentVertice] = true;
    dis[currentVertice] = low[currentVertice] = ++t;

    for (list<int>::iterator i = this->adjMatrix[currentVertice].begin(); i != this->adjMatrix[currentVertice].end(); ++i) {
        int tmpVertice = *i;

        if (!visited[tmpVertice]) {
            par[tmpVertice] = currentVertice;
            connections(tmpVertice, visited, dis, low, par);
            if (low[tmpVertice] > dis[currentVertice])
                cout << currentVertice << "->" << tmpVertice << endl;
        }
        else if (tmpVertice != par[currentVertice])
            low[currentVertice] = min(low[currentVertice], dis[tmpVertice]); 
    }
}

void Graph::findMaxCut() {
    omp_init_nest_lock(&lock);
    bool* visited = new bool[this->numberVertices];
    int* dis = new int[this->numberVertices];
    int* low = new int[this->numberVertices];
    int* par = new int[this->numberVertices];
    int i;

#pragma omp parallel for private(i) shared(par, visited)
    for (i = 0; i < this->numberVertices; i++) {
        par[i] = -1;
        visited[i] = false;
    }
#pragma omp for
    for (i = 0; i < this->numberVertices; i++) {
        omp_set_nest_lock(&lock);
        if (visited[i] == false)
            connections(i, visited, dis, low, par);
        omp_unset_nest_lock(&lock);
    }
    omp_destroy_nest_lock(&lock);
}

void Graph::createGraph(Graph& G, int numberEdges)
{
    int v, w;
    for (int i = 0; i < numberEdges; i++) {
        cout << "¬ведите начало и конец ребра" << endl;
        cin >> v >> w;
        if (!G.addEdge(v, w)) {
            cout << "-> ¬ведены недопустимые данные" << endl;
        }
    }
}

void Graph::printGraph() {

    for (int i = 0; i < this->numberVertices; i++) {
        cout << "\n—писок смежности вершин дл€ " << i << "-й вершины \n" << i;
        list<int>::iterator j;
        for (j = this->adjMatrix[i].begin(); j != this->adjMatrix[i].end(); ++j) {
            if (j != this->adjMatrix[i].end()--) {
                cout << "->" << *j;
            }
        }
        cout << "\n";
    }
}
