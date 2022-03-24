#include <iostream>
#include <fstream>

using namespace std;

int matrice_ad[10][10], lista_ad[10][10], matrice_inc[10][10];

int main() {
    ifstream in("graf.txt");
    int i, j, nr_muchii, nr_varfuri, m1, m2, s, nr, s1, s2, ok, inf = 99999, matrice_dist[10][10], k;
    in >> nr_varfuri >> nr_muchii;
    for (i = 1; i <= nr_muchii; i++)
    {
        in >> m1 >> m2;
        matrice_ad[m1][m2] = 1;
        matrice_ad[m2][m1] = 1;

        matrice_inc[m1][i] = 1;
        matrice_inc[m2][i] = 1;
    }

    cout << "Matrice de adiacenta: \n";
    for (i = 1; i <= nr_varfuri; i++)
    {
        for (j = 1; j <= nr_varfuri; j++)
        {
            cout << matrice_ad[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nNoduri izolate: \n";
    nr = 0;
    for (i = 1; i <= nr_varfuri; i++)
    {
        s = 0;
        for (j = 1; j <= nr_varfuri; j++)
        {
            s = s + matrice_ad[i][j];
        }
        if (s == 0)
            cout << i << " ";
        else
            nr++;
    }
    if (nr == nr_varfuri)
        cout << "Nu exista noduri izolate!";
    cout << "\n";


    cout << "\nMatricea distantelor:\n";
    for (i = 1; i < nr_varfuri; ++i)
        for (j = i; j <= nr_varfuri; ++j)
            if (!matrice_ad[i][j] and i != j)
            {
                matrice_dist[i][j] = inf;
                matrice_dist[j][i] = inf;
            }
            else
            {
                matrice_dist[i][j] = matrice_ad[i][j];
                matrice_dist[j][i] = matrice_ad[i][j];
            }

    for (k = 1; k <= nr_varfuri; ++k)
        for (i = 1; i <= nr_varfuri; ++i)
            for (j = 1; j <= nr_varfuri; ++j)
                if (matrice_dist[i][k] != inf and matrice_dist[k][j] != inf)
                    matrice_dist[i][j] = min(matrice_dist[i][j], matrice_dist[i][k] + matrice_dist[k][j]);

    for (i = 1; i <= nr_varfuri; i++)
    {
        for (j = 1; j <= nr_varfuri; j++)
            if (matrice_dist[i][i] == inf)
                cout << "INF ";
            else
                cout << matrice_dist[i][j] << "    ";
        cout << "\n";
    }


    cout << "\nGraf regulat: \n";
    ok = 1;
    s1 = 0;
    for (j = 1; j <= nr_varfuri; j++)
        s1 = s1 + matrice_ad[1][j];

    for (i = 2; i <= nr_varfuri; i++)
    {
        s2 = 0;
        for (j = 1; j <= nr_varfuri; j++)
        {
            s2 = s2 + matrice_ad[i][j];
        }
        if (s2 != s1)
        {
            ok = 0;
            break;
        }
    }
    if (ok == 0)
        cout << "Nu este regulat!";
    else
        cout << "Este regulat!";



}