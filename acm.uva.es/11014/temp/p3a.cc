#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long i64;

#define foreach_divisor(d,no) \
        for (int d=2, Num=(no); d*d<=Num; d++) \
        if (Num%d == 0) \
        for (int k=0; k<2; k++, D=Num/d) \
        if (k == 0 || d*d != Num)

#define N 50

int phi[N], pf[N];
i64 a[N], phi_sum[N];

i64 cube(i64 n) { return n*n*n; }

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

        phi_sum[0] = 0;
        for (int i = 1; i < N; i++) phi_sum[i] = phi_sum[i-1] + phi[i];

        a[1] = 26;
        for (i64 n = 2; n < N; n++) {
                a[n] = cube(2*n+1)-1;

                for (int g = 2; g <= n; g++)
                        a[n] -= a[n/g];
        }

/*
        [n/d] = t
        t <= n/d < t+1
        td <= n <= td+d-1
        td <= n        d <= n/t
        n+1 <= (t+1)d  (n+1)/(t+1) <= d <= n/t

                for (int g = 2; g < n; g++)
                        if (__gcd(g,n) > 1)
                                O[n] += 48LL * phi_sum[n/g];
*/

        i64 n;
        while (scanf("%lld", &n) == 1 && n > 0)
                printf("%lld\n", a[n/2]);
}
