#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

long long MOD = 1051962371;
long long D[101];            // derangements
long long P[101];            // perms
long long C[101][101];       // binomials

int main()
{
    int T;
    cin >> T;

    D[0] = 1;
    D[1] = 0;
    for (int n = 2; n <= 100; n++)
        D[n] = ((n - 1) * (D[n-1] + D[n-2])) % MOD;

    P[0] = 1;
    for (int n = 1; n <= 100; n++)
        P[n] = (n * P[n-1]) % MOD;

    for (int n = 0; n <= 100; n++) {
        C[n][0] = 1;
        for (int k = 1; k <= n; k++)
            C[n][k] = (C[n-1][k] + C[n-1][k-1]) % MOD;
    }

    for (int cs = 1; cs <= T; cs++) {
        int g, c;
        cin >> g >> c;

        long long res = 0;
        for (int cc = c; cc <= g; cc++)
            res = (res + C[g][cc] * D[g-cc]) % MOD;

        cout << res << "\n";
    }
}
