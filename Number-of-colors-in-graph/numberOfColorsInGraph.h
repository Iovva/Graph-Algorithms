#ifndef ULT_LAB_GRAFURI_H_
#define ULT_LAB_GRAFURI_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int g_vertexes, g_edges;
vector<int> g_colors;
vector<bool> g_visited;
vector<vector<bool>> g_graph;

int maxColor = 0;

// algoritm BFS
void BFS(int startNode);

// returneaza vecinii unui varf
vector<int> getNeighbors(int currentVertex, vector<vector<bool>> g_graph);

// returneaza vecinii vizitati ai unui varf
vector<int> getVisitedNeighbors(const vector<int>& neighbors, const vector<bool>& g_visited);

// returneaza cea mai mica culoare posibila pentru varful curent
int generateColor(const vector<int>& visitedNeighbors);

// returneaza true daca culoarea este folosita de un vecin, false in caz contrar
bool colorIsUsed(int color, const vector<int>& visitedNeighbors);

#endif