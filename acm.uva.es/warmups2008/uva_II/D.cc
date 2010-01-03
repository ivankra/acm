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

#define MOD 100000000

LL C[1024][1024];
int n;

int main()
{
    LL t;

    for (n = 0; n <= 1000; n++) {
        C[n][0] = 1;
        for (int k = 1; k <= n; k++)
            C[n][k] = (C[n-1][k-1] + C[n-1][k]) % MOD;
    }

    while (scanf("%d", &n) == 1 && n > 0) {
        int ans = 0;
        for (int z = 0; z <= n; z++) {
            for (int y = 0; y+z <= n; y++) {
                // (x+z)(y+z) = zn
                // x(y+z) = zn-z(y+z)
                // 0 <= x <= n-y-z

                if (y+z == 0) continue;
                int rhs = z*n-z*(y+z);
                if (rhs < 0 || rhs%(y+z) != 0) continue;
                int x = rhs / (y+z);

                //for (int x = 0; x <= n-y-z; x++)
                {
                    if (x+z == 0 || y+z == 0) continue;
                    if ((x+z)*(y+z) == z*n) {
                        t = C[n][x];
                        t = (t * (LL)C[n-x][y]) % MOD;
                        t = (t * (LL)C[n-x-y][z]) % MOD;
                        //printf("x=%d y=%d z=%d  t=%lld\n",x,y,z,t);
                        ans = (ans + t) % MOD;
                    }
                }
            }
        }

        printf("%d\n", ans);
    }


}
