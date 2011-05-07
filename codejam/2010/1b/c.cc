#include <cstdio>
#include <cstring>
typedef long long LL;

LL memo[512][512], C[512][512];
LL MOD = 100003;

LL f(int n, int k) {
    LL &res = memo[n][k];
    if (res != -1)
        return res;

    if (k <= 0) return res = 0;
    if (k == 1) return res = (n >= 2 ? 1 : 0);

    res = 0;
    for (int m = 0; m <= n-k-1; m++) {
        if (k - 1 - m < 0) continue;

        res += f(k, k-1-m) * C[n-k-1][m];
        res %= MOD;
    }

    return res;
}

LL solve(int n) {
    LL res = 0;
    for (int k = 1; k <= n-1; k++)
        res = (res + f(n, k)) % MOD;
    return res;
}

int main()
{
    memset(C, 0, sizeof(C));
    for (int i = 0; i < 512; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }

    memset(memo, 0xff, sizeof(memo));

    int T, N;
    scanf("%d", &T);
    for (int cs = 1; cs <= T; cs++) {
        scanf("%d", &N);
        printf("Case #%d: %lld\n", cs, solve(N));
    }
}
