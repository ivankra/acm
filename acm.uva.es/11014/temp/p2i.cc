#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long i64;

//#define N 100010
#define N 50

int phi[N], pf[N];
i64 Q[N], O[N];

#define foreach_divisor(D,N) \
        for (int D=2, Num=(N); D*D<=Num; D++) \
        if (Num % D == 0) \
        for (int k=0; k<2; k++, D=Num/D) \
        if (k == 0 || D*D != Num)

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
                O[n] = O[n-1] + 26LL + 24LL*(n-1-phi[n]);

                for (int g = 2; g < n; g++)
                        if (__gcd(g,n) > 1)
                                O[n] += 6 * Q[n/g];

                foreach_divisor(d, n)
                        O[n] -= 48 * phi[n/d];
        }

        i64 n;
        while (scanf("%lld", &n) == 1 && n > 0)
                printf("%lld\n", (n+1)*(n+1)*(n+1)-O[n/2]);
}
