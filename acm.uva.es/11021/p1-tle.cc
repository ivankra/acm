#include <cstdio>
#include <cmath>

int main()
{
        int T, cs=1;
        for (scanf("%d", &T); cs <= T; cs++) {
                int n, k, m;
                double P[1024];

                scanf("%d %d %d", &n, &k, &m);
                for (int i = 0; i < n; i++) scanf(" %lf", &P[i]);

                double f = 0;
                for (int i = 1; i <= m; i++) {
                        double g = 0;
                        for (int j = 0; j < n; j++)
                                g += P[j] * pow(f, j);
                        f = g;
                }

                printf("Case #%d: %.7f\n", cs, pow(f, (double)k));
        }
        return 0;
}
