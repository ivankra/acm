#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long i64;

//#define N 100010
#define N 50

int phi[N], pf[N];
i64 Q[N], O[N];

int main()
{
        for (int i = 0; i < N; i++) phi[i] = 1;
        memset(pf, 0, sizeof(pf));
        pf[1] = 1;
        for (int p = 2; p < N; p++) {
                if (pf[p] != 0) continue;
                for (int q = p; q < N; q += p) {
                        phi[q] *= p-1;
                        pf[q] = p;
                }
                if (p < 400)
                for (int m = p*p; m < N; m *= p)
                for (int q = m; q < N; q += m)
                        phi[q] *= p;                      
        }

        Q[1] = 8;
        for (int i = 2; i < N; i++) Q[i] = Q[i-1] + 8LL * phi[i];

        O[1] = 1;
        for (int n = 2; n < N; n++) {
                O[n] = O[n-1];

                for (int g = 2; g < n; g++)
                if (__gcd(g,n) > 1) {
                        O[n] += 6 * Q[(n-1)/g];
                }

                // |n|,|n|,x
                O[n] += 3*4 * 2*(n-1-phi[n]);

                O[n] += 12;     // |x|=n, |y|=n, z=0
                O[n] += 8;      // |x|=n, |y|=n, |z|=n
                O[n] += 6;      // |x|=n, 0, 0
        }

        i64 n;
        while (scanf("%lld", &n) == 1 && n > 0)
                printf("%lld\n", (n+1)*(n+1)*(n+1)-O[n/2]);
}
