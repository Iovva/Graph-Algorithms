#include <bits/stdc++.h>

using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");

int d[107];
int c[107];
int cnt[107];

int main()
{
    int m;
    fin >> m;
    for(int i = 0; i < m; ++i)
        fin >> d[i];
    for(int i = 0; i <= m; ++i)
        c[i] = -1;
    for(int i = 0; i < m; ++i)
        cnt[d[i]]++;
    for(int i = 0; i < m; ++i)
    {
        int nod = 0;
        for(nod = 0; nod < m; ++nod)
            if(cnt[nod] == 0)
                break;
        int father = d[i];
        c[nod] = father;
        cnt[father]--;
        cnt[nod] = 1e9;
    }
    fout << m + 1 << '\n';
    for(int i = 0; i <= m; ++i)
    {
        fout << c[i] << ' ';
    }
}
