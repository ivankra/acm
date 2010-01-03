// Precomputes a table of values of phi and gpf (greatest prime factor) for
// integers from 1 to N.
#include <cstdio>
#include <cstring>

#define N 110
#define SQRT_N 12

int phi[N], pf[N];

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
                if (p < SQRT_N)
                for (int m = p*p; m < N; m *= p)
                for (int q = m; q < N; q += m)
                        phi[q] *= p;                      
        }

        for (int i = 1; i < N; i++)
                printf("%5d: phi=%-2d pf=%d\n", i, phi[i], pf[i]);
}
