#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

void moore()
{
    int nr_varfuri, aux, nr_muchii;
    int m1, m2;
    int matrice_ad[10][10], dist[105];
    queue <int> q;
    memset(dist, 10000, sizeof(dist));
    memset(matrice_ad, 0, sizeof(matrice_ad));
    ifstream fin("graf1.txt");
    fin >> nr_varfuri >> nr_muchii;
    for (int i = 1; i <= nr_muchii; i++)
    {
        fin >> m1 >> m2;
        matrice_ad[m1][m2] = 1;
    }
    int start = 0;

    cin >> start;

    dist[start] = 0;


    q.push(start);

    while (!q.empty())
    {
        aux = q.front();
        q.pop();

        for (int i = 1; i <= nr_varfuri; i++)
        {
            if (matrice_ad[aux][i] != 0)
                if (dist[i] > dist[aux] + 1)
                {
                    dist[i] = dist[aux] + 1;
                    q.push(i);
                }
        }
    }

    for (int i = 1; i <= nr_varfuri; i++)
        cout << dist[i] << ' ';
}

int main() {
    ifstream in("graf.txt");
    int matrice_ad[10][10], matrice_transitiva[10][10], v[100];
    memset(matrice_ad, 0, sizeof(matrice_ad));
    memset(matrice_transitiva, 0, sizeof(matrice_transitiva));
    memset(v, 0, sizeof(v));
    int i, j, nr_muchii, nr_varfuri, m1, m2, k;
    in >> nr_varfuri >> nr_muchii;
    for (i = 1; i <= nr_muchii; i++)
    {
        in >> m1 >> m2;
        matrice_ad[m1][m2] = 1;
        matrice_transitiva[m1][m2] = 1;
    }

    cout << "Matrice de adiacenta: \n\n";
    for (i = 1; i <= nr_varfuri; i++)
    {
        for (j = 1; j <= nr_varfuri; j++)
        {
            cout << matrice_ad[i][j] << " ";
        }
        cout << "\n";
    }
 
    cout << "\nMoore:\n";
    moore();
}