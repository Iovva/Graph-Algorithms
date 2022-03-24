#include <bits/stdc++.h>

using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");

int d[107];
int s[107];
int cnt;
int c[107];

int main()
{
    int n;
    fin >> n;
    for(int i = 0; i < n; ++i)
    {
        fin >> d[i];
        s[d[i]]++;
    }
    int cp = 0;
    bool ok = false;
    while(!ok)
    {
        for(int i = 0; i < n; i++)
        {
            ok = true;
            if(s[i] == 0)
            {
                ok = false;
                cp = i;
                s[i]--;
                if(d[i] != -1)
                {
                    s[d[i]]--;
                }
                c[cnt++] = d[cp];
                break;
            }
        }
    }
    fout << cnt - 1 << '\n';
    for(int i = 0; i < cnt - 1; ++i)
    {
        fout << c[i] << ' ';
    }
}
