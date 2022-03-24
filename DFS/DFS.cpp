#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

void dfs(int a[10][10], int n, int start, int viz[100])
{
    viz[start] = 1;
    cout << start << ' ';
    for (int i = 1; i <= n; i++)
        if (viz[i] == 0 && a[start][i] == 1)
            dfs(a, n, i, viz);
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

    cout << "DFS:\n";
    memset(v, 0, sizeof(v));
    dfs(matrice_ad, nr_varfuri, s, v);

}