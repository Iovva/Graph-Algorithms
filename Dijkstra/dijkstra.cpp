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


//1
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

int extract_min(int& k, int nr_noduri)
{
    int distMin = Inf;
    int vfMin = nr_noduri + 1;
    int poz = -1;
    for (int i = 0; i < k; i++)
    {
        int nod = c[i];
        if (dist[nod] < distMin)
        {
            poz = i;
            distMin = dist[nod];
            vfMin = nod;
        }
    }
    for (int i = poz; i < k - 1; i++)
        c[i] = c[i + 1];
    c[k - 1] = 0;
    k--;
    return vfMin;
}

void Dijkstra(int start, int nr_noduri)
{
    int k, u, v;
    initializare(start, nr_noduri);
    for (k = 0; k < nr_noduri; k++)
        c[k] = k;
    k = nr_noduri; // k devine nr de varfuri din coada
    while (k != 0)
    {
        u = extract_min(k, nr_noduri);
        for (v = 0; v < nr_noduri; v++)
            if (m[u][v] != 0)
                relax(u, v);
    }
}


int main()
{
    citire();
    int start;
    cout << "---- 1) Dijkstra ----\n\n" << "Nodul de la care se porneste: ";
    cin >> start;
    Dijkstra(start, nr_noduri);
    for (int i = 0; i < nr_noduri; i++)
        cout << "Din nodul " << i << " distanta e " << dist[i] << '\n';
    return 0;
}