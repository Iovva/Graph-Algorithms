#include <iostream>
#include <fstream>
#define Inf 1000000

using namespace std;

ifstream fin("graf.txt");

int m[105][105], dist[105], parinte[105], c[105], nr_noduri;

void citire()
{
    int x, y, cost;
    fin >> nr_noduri;
    while (fin >> x >> y >> cost)
        m[x][y] = cost;
}


//2
void initializare(int start, int nr_noduri)
{
    for (int i = 0; i < nr_noduri; i++)
    {
        parinte[i] = -1;
        dist[i] = Inf;
    }
    dist[start] = 0;
}

void relax(int u, int v)
{
    if (dist[v] > dist[u] + m[u][v])
    {
        dist[v] = dist[u] + m[u][v];
        parinte[v] = u;
    }
}

bool Bellman(int start, int nr_noduri)
{
    int i, u, v;
    initializare(start, nr_noduri);
    for (i = 0; i < nr_noduri; i++)
        for (u = 0; u < nr_noduri; u++)
            for (v = 0; v < nr_noduri; v++)
                if (m[u][v] != 0)
                    relax(u, v);

    for (u = 0; u < nr_noduri; u++)
        for (v = 0; v < nr_noduri; v++)
            if (m[u][v] != 0)
                if (dist[v] > dist[u] + m[u][v])
                    return false;
    return true;
}


int main()
{
    citire();
    int start;
    cout << "---- 2) Bellman ----\m\n" <<"Nodul de la care se porneste: ";
    cin >> start;
    bool ok = Bellman(start, nr_noduri);
    if (ok)
    {
        for (int i = 0; i < nr_noduri; i++)
            cout << "Din nodul " << i << " distanta este " << dist[i] << '\n';
    }
    else
        cout << "Nu exista solutie !\n";
    return 0;
}