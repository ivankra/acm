#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
typedef unsigned long long ULL;
#define FOREACH(it, v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()
#define REP(i,n) for(int i=0;i<(n);++i)

#define MOD 100000007 

int N,K,S;
int f[2][1<<15], g[2][1<<15];

int solve()
{
    for (int s = 0; s <= S; s++) f[0][s] = 0;
    f[0][0] = 1;

    for (int s = 0; s <= S; s++) g[0][s] = (s <= K-1 ? 1 : 0);

    for (int nn = 1; nn <= N; nn++) {
        int n = nn & 1;
        f[n][0] = 0;
        f[n][1] = f[n^1][0];

        for (int s = 2; s <= S; s++) {
            LL t = f[n^1][s-1] + f[n][s-1] + g[n^1][s-2];
            if (s >= K+1)
                t -= (K+1)*(LL)f[n^1][s-(K+1)];
            f[n][s] = t % MOD;
            if (f[n][s] < 0) f[n][s] += MOD;
        }

        g[n][0] = f[n][0];
        for (int s = 1; s <= S; s++) {
            g[n][s] = g[n][s-1] + f[n][s];
            if (g[n][s] >= MOD) g[n][s] -= MOD;

            if (s >= K) {
                g[n][s] -= f[n][s-K];
                if (g[n][s] < 0) g[n][s] += MOD;
            }
        }
    }

    return (f[N&1][S] % MOD + MOD) % MOD;
}

int main()
{
    while (cin >> N >> K >> S) {
        if (N == 0) break;
        cout << solve() << endl;
    }
}
