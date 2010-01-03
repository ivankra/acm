#include <cstdio>
typedef unsigned long long u64;

unsigned a[1024], mod, C[1024];
int n;

int main()
{
        while (scanf("%d %u", &n, &mod) == 2 && n > 0 && mod > 0) {
                for (int i = 1; i <= n; i++) scanf("%u", &a[i]);

                for (int i = 0; i <= n; i++) C[i] = 0;
                C[0] = 1;

                for (int m = 1; m <= n; m++) {
                        C[0] = 1;
                        for (int k = m; k >= 1; k--)
                                C[k] = (C[k] + (u64)C[k-1]*(u64)a[m]) % (u64)mod;
                }

                unsigned best = 0;
                for (int k = 0; k <= n; k++) best >?= C[k]%mod;
                printf("%u\n", best%mod);
        }
}
