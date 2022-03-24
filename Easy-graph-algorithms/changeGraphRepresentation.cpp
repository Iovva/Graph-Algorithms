#include <iostream>
#include <fstream>

using namespace std;

int matrice_ad[10][10], lista_ad[10][10], matrice_inc[10][10];

int main() {
    ifstream in("graf.txt");
    int i, j, nr_muchii, nr_varfuri, m1, m2;
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

    cout << "\nMatrice de incidenta: \n";
    for (i = 1; i <= nr_varfuri; i++)
    {
        for (j = 1; j <= nr_muchii; j++)
        {
            cout << matrice_inc[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nLista de adiacenta: \n";
    for (i = 1; i <= nr_varfuri; i++)
    {
        cout << i << " - ";
        for (j = 1; j <= nr_varfuri; j++)
            if (matrice_ad[i][j] == 1)
                cout << j << " ";
        cout << "\n";
    }
}