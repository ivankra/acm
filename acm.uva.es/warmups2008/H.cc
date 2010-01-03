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
typedef long long LL;

#define MOD 1000000009

int N, seq[100010];
int sum[21][100010];
LL C[32][32];

int main()
{
    int T, Q, K, A, B;
    scanf("%d", &T);

    memset(C, 0, sizeof(C));
    for (int n = 0; n < 32; n++) {
        C[n][0] = 1;
        for (int k = 1; k <= n; k++)
            C[n][k] = (C[n-1][k-1] + C[n-1][k]) % MOD;
    }

    for (int cs = 1; cs <= T; cs++) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++)
            scanf("%d", &seq[i]);

        for (int k = 0; k <= 20; k++) sum[k][0] = 0;
        for (int i = 1; i <= N; i++) {
            LL t = seq[i] % MOD;
            for (int j = 0; j <= 20; j++) {
                sum[j][i] = (sum[j][i-1] + t) % MOD;
                t = (t * i) % MOD;
            }
        }

        scanf("%d", &Q);
        for (int q = 1; q <= Q; q++) {
            scanf("%d %d %d", &K, &A, &B);

            LL res = 0;
            LL w = ((-A+1+MOD) % MOD + MOD) % MOD;
            LL ww = 1;

            for (int m = K; m >= 0; m--) {
                res += (((C[K][m] * ww) % MOD) * (sum[m][B] - sum[m][A-1])) % MOD;
                ww = (ww * w) % MOD;
            }

            res %= MOD;
            res = (res + MOD) % MOD;

            printf("%lld\n", res);
        }
    }
}
