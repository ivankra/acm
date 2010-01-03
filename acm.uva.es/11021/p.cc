#include <cstdio>
#include <cmath>

double a[1024];
int n;

double P(double x) {
        double r = 0;
        for (int j = n-1; j >= 0; j--)
                r = r * x + a[j];
        return r;
}

int main()
{
        int T, cs=1;
        for (scanf("%d", &T); cs <= T; cs++) {
                int k, m;

                scanf("%d %d %d", &n, &k, &m);
                for (int i = 0; i < n; i++) scanf(" %lf", &a[i]);

                double x = 0;
                for (int i = 0; i < m; i++)
                        x = P(x);

                printf("Case #%d: %.7f\n", cs, pow(x, k));
        }
        return 0;
}
