// Obvious strategy is to shuffle elements in each single permutation cycle
#include <cstdio>
#include <cstdlib>
#include <cmath>

typedef long double real_t;

real_t cds[1024][1024];  // cycle distribution stats, [n][k] = total number of k-cycles in all n! permutations of n
real_t fact[1024], lfact[1024];
real_t F[1024];

int main()
{
    fact[0] = 1;
    lfact[0] = 0;
    for (int i = 1; i <= 1000; i++) {
        fact[i] = fact[i-1] * i;
        lfact[i] = lfact[i-1] + log((real_t)i);
    }

    cds[0][0] = 1;
    cds[1][1] = 1;

    for (int n = 2; n <= 10; n++) {
        for (int k = 1; k <= n; k++) {
            real_t count = exp(lfact[n-1] - lfact[n-k]);  // (n-1 choose k-1)*(k-1)! - number of k-cycles containing first element

            if (k == n) {
                cds[n][n] = count;
                break;
            }

            for (int i = 0; i <= n-k; i++)
                cds[n][i] += cds[n-k][i] * count;
            cds[n][k] += count * fact[n-k];
        }

/*        printf("n=%d:", n);
        for (int k = 1; k <= n; k++)
            printf(" %d:%.10Lg", k, cds[n][k]);
        printf("\n");*/
    }

    // F[n] = number of moves to sort a single n-length cycle
    F[0] = 0;
    F[1] = 0;
    for (int n = 2; n <= 1000; n++) {
/*        F[n] = 0;
        for (int k = 1; k < n; k++)
            F[n] += cds[n][k] * F[k];
        F[n] /= fact[n];
        F[n] += 1;
        F[n] /= 1 - cds[n][n]/fact[n];

        printf("F[%d] = %.10Lg\n", n, F[n]);*/

        //hypothesis: F[n]=n for n>=2
        F[n] = n;
    }

    int T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        int N, A[1024];
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
            A[i]--;
        }

        real_t res = 0;
        for (int i = 0; i < N; i++) {
            if (A[i] != -1) {
                int len = 0;
                for (int j = i; A[j] != -1; len++) {
                    int k = A[j];
                    A[j] = -1;
                    j = k;
                }
                res += F[len];
            }
        }
        printf("Case #%d: %.9Lg\n", cs, res);
    }
}
