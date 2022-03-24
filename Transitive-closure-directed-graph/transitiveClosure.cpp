#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

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

    for (k = 1; k <= nr_varfuri; k++)
        for (i = 1; i <= nr_varfuri; i++)
            for (j = 1; j <= nr_varfuri; j++)
                if (matrice_transitiva[i][j] == 0)
                    matrice_transitiva[i][j] = (matrice_transitiva[i][k] && matrice_transitiva[k][j]);
    
    cout << "\nMatricea inchiderii tranzitive: \n\n";
    for (i = 1; i <= nr_varfuri; i++)
    {
        for (j = 1; j <= nr_varfuri; j++)
        {
            cout << matrice_transitiva[i][j] << " ";
        }
        cout << "\n";
    }
}