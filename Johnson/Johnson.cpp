#include <iostream>
#include <fstream>
#define Inf 1000000

using namespace std;

ifstream fin("graf.txt");

int dist[105], parinte[105], c[105];

void citire(int m[105][105], int costuri[105][105], int& nr_noduri)
{
	int x, y, cost;
	fin >> nr_noduri;
	while (fin >> x >> y >> cost)
	{
		m[x][y] = 1;
		costuri[x][y] = cost;
	}
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

void relax(int u, int v, int costuri[105][105])
{
	if (dist[v] > dist[u] + costuri[u][v])
	{
		dist[v] = dist[u] + costuri[u][v];
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

void Dijkstra(int m[105][105], int costuri[105][105], int nr_noduri, int start)
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
				relax(u, v, costuri);
	}
}

bool Bellman(int m[105][105], int costuri[105][105], int nr_noduri, int start)
{
	int i, u, v;
	initializare(start, nr_noduri);
	for (i = 0; i < nr_noduri; i++)
		for (u = 0; u < nr_noduri; u++)
			for (v = 0; v < nr_noduri; v++)
				if (m[u][v] != 0)
					relax(u, v, costuri);

	for (u = 0; u < nr_noduri; u++)
		for (v = 0; v < nr_noduri; v++)
			if (m[u][v] != 0)
				if (dist[v] > dist[u] + m[u][v])
					return false;
	return true;
}

void Johnson(int m[105][105], int costuri[105][105], int nr_noduri, int start)
{
	int newMatrice[105][105];
	int newCosturi[105][105];
	int newN = nr_noduri;

	for (int i = 0; i < nr_noduri; i++)
		for (int j = 0; j < nr_noduri; j++)
		{
			newMatrice[i][j] = m[i][j];
			newCosturi[i][j] = costuri[i][j];
		}

	for (int i = 0; i < nr_noduri; i++)
	{
		newMatrice[newN][i] = 1;
		newCosturi[newN][i] = 0;
	}

	for (int i = 0; i < newN; i++)
	{
		newMatrice[i][newN] = 0;
		newCosturi[i][newN] = 0;
	}

	if (!Bellman(newMatrice, newCosturi, newN, newN))
	{
		cout << -1;
		return;
	}

	for (int i = 0; i < nr_noduri; i++)
		for (int j = 0; j < nr_noduri; j++)
			costuri[i][j] = costuri[i][j] + dist[i] - dist[j];
	Dijkstra(m, costuri, nr_noduri, start);
}
int main()
{
	int m[105][105], costuri[105][105], nr_noduri, start;
	memset(m, 0, sizeof(m));
	memset(costuri, 0, sizeof(costuri));
	citire(m, costuri, nr_noduri);
	cout << "---- 3) Johnson ----\n\n" << "Introduceti nodul de unde se porneste: ";
	cin >> start;
	Johnson(m, costuri, nr_noduri, start);
	for (int i = 0; i < nr_noduri; i++)
		cout << "Din nodul " << i << " distanta e " << dist[i] << '\n';
	return 0;
}
