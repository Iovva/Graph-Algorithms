#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

void bfs(int a[10][10], int n, int start, int viz[100])
{
    int c[105], p, u, vf;
    // c - coada
    p = u = 1;
    c[u] = start;
    viz[start] = 1;
    while (p <= u)
    {
        vf = c[p];
        p++;
        for (int i = 1; i <= n; i++)
            if (a[vf][i] != 0 && viz[i] == 0)
            {
                u++;
                c[u] = i;
                viz[i] = 1;
            }
    }
    for (int i = 1; i <= u; i++)
        cout << c[i] << ' ';
    cout << "\nDistanta fata de " << start << " este " << u << "\n\n";
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

    cout << "BFS:\n";
    int s = 1;
    bfs(matrice_ad, nr_varfuri, s, v);

}