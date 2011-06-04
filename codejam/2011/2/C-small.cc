#include <cstdio>
#include <cstring>

int factor(int n, int *pi)
{
    int flag = 0;

    for (int p = 2; p*p <= n; p++) {
        int c = 0;
        while (n % p == 0) { c++; n /= p; }

        if (c > pi[p]) {
            pi[p] = c;
            flag = 1;
        }
    }

    if (n > 1) {
        int c = 1, p = n;

        if (c > pi[p]) {
            pi[p] = c;
            flag = 1;
        }
    }

    return flag;
}

int gcd(int x, int y)
{
    return x == 0 ? y : gcd(y % x, x);
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        int N;
        scanf("%d", &N);

        printf("Case #%d: ", cs);
        if (N == 1) { printf("0\n"); continue; }  //???

        int max;
        {
            int pi[1024];
            memset(pi, 0, sizeof(pi));

            int count = 1;
            for (int i = 2; i <= N; i++)
                count += factor(i, pi);

            max = count;
        }

        int min;
        {
            int pi[1024];
            memset(pi, 0, sizeof(pi));

            int count = 0;

            int is_prime[1024];
            memset(is_prime, 0, sizeof(is_prime));

            for (int p = 2; p <= N; p++) {
                if (is_prime[p]) {
                    for (int q = 2*p; q <= N; q += p)
                        is_prime[q] = 0;
                }
                int q = p;
                while (q*p <= N)
                    q *= p;
                count += factor(q, pi);
            }

            for (int i = N; i >= 2; i--)
                count += factor(i, pi);

            min = count;
        }

        fprintf(stderr, "%d: min=%d max=%d\n", N, min, max);

        printf("%d\n", max - min);
    }
}
