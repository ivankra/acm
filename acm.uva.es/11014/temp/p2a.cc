#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long i64;

//#define N 100010
#define N 1000

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
                O[n] = O[n-1];  // + 6LL * Q[n-1] + 24LL * phi[n];
                for (int g = 2; g*g <= n; g++) {
                        if ((n%g) == 0) {
                                O[n] += 6LL * Q[n/g];
                                if (g*g != n) O[n] += 6LL * Q[n/(n/g)];
                        }
                }
// ((x,y)=g, n)>1
//                        if (__gcd(g,n) == 1) O[n] += 6LL * Q[n/g];
        }

        i64 n;
        while (scanf("%lld", &n) == 1 && n > 0)
                printf("%lld\n", (n+1)*(n+1)*(n+1)-O[n/2]);
}
