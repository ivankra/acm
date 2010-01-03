#include <cstdio>
typedef long long i64;

i64 a[100001]={0,26};

int main()
{
        for (int n = 2, d, e; n <= 100000; n++) {
                a[n] = a[n-1] + 24*(i64)n*(i64)n - 24;
                for (d = 2; d*d < n; d++) if(n%d == 0) {
                        e = n/d;
                        a[n] -= a[d] - a[d-1];
                        a[n] -= a[e] - a[e-1];
                }
                if (d*d == n) a[n] -= a[d] - a[d-1];
        }

        i64 n;
        for (int cs = 1; scanf("%lld", &n) == 1 && n > 0; cs++)
                printf("Crystal %d: %lld\n", cs, a[n/2]);
}
