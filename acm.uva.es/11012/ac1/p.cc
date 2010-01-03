#include <stdio.h>
#include <stdlib.h>

int x[100010], y[100010], z[100010], n;

int dist(int a, int b) { return abs(x[a]-x[b])+abs(y[a]-y[b])+abs(z[a]-z[b]); }

int main()
{
        int cs=1, t;
        for (scanf("%d", &t); cs <= t && scanf("%d", &n) == 1; cs++) {
                for (int i = 0; i < n; i++) scanf("%d %d %d", &x[i], &y[i], &z[i]);

                int w[8], k = 0;
                for (int dx = -1; dx <= 1; dx += 2)
                for (int dy = -1; dy <= 1; dy += 2)
                for (int dz = -1; dz <= 1; dz += 2) {
                        w[k] = 0;
                        int v = -0x3fffffff;
                        for (int i = 0; i < n; i++) {
                                int V = dx*x[i] + dy*y[i] + dz*z[i];
                                if (V > v || i == 0) { v = V; w[k] = i; }
                        }
                        k++;
                }

                int best = 0;
                for (int i = 0; i < n; i++)
                        for (int j = 0; j < 8; j++)
                                best >?= dist(i, w[j]);

                printf("Case #%d: %d\n", cs, best);
        }
        return 0;
}
