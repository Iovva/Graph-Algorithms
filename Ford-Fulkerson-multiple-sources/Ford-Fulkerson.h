#ifndef FORD_FULKERSON_H_
#define FORD_FULKERSON_H_

#include<iostream>
#include<fstream>
#include <queue>
using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

vector<vector<int>> g_graph;
vector<vector<int>> g_residualGraph;
vector<int> g_parent;
int g_vertexes;
int g_edges;
int g_sources;

// algoritmul Ford-Fulkerson
int fordFulkerson();

// initializeaza matricea globala a grafului rezidual si vectorul global al parintilor
void initFordFulkerson();

// procedura BFS
// returneaza true daca gaseste un drum de la sursa la destinatie
// false, in caz contrar
// modifica vectorul de parinti pentru a reflecta drumul nou gasit ( chiar si incomplet )
bool BFS(int g_vertexes, int source, int destination);

#endif
